/*
 * Copyright (c) 2017 Bitshares, and contributors.
 *
 * The MIT License
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#pragma once
#include <graphene/chain/protocol/operations.hpp>
#include <graphene/db/generic_index.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <map>
#include <string>

namespace graphene { namespace chain {
   class database;

   /**
    * @class skyStreet_object
    * @ingroup object
    * @ingroup implementation
    */
   class skyStreet_object : public graphene::db::abstract_object<skyStreet_object>
   {
      public:
       
         static const uint8_t space_id = implementation_ids;
         static const uint8_t type_id  = impl_skyStreet_object_type;

       enum ExchangeType{
           Sell,
           Buy
       };
       
       enum DeliveryType{
           // 1.buyer paid , 2.seller delivery goods and finish .
           SellPrior,
           // 1.buyer paid and lock money, 2.seller dilivery , 3. buyer comfirm , unlock money to seller
           Normal
       };
       enum ExchangeQuantityType{
           Multi,
           Single
       };
       
       enum GoodType{

           OnChain,

           OffChain
       };
       
       ExchangeType                                 exchange_type;
       DeliveryType                                 delivery_type;
       ExchangeQuantityType                         exchange_quantity_type;
       GoodType                                     good_type;
       account_id_type                              seller;
       account_id_type                              buyer;
       //if OnChain ,
       asset                                        on_chain_amount=asset();
       share_type                                   amount=0;
       
       vector<skyStreet_id_type>                    sub_sky_street_object;
       
       std::string                                  description;
       
       std::map<std::string,std::string>            extras;
       
       
   };
    struct by_account;
    struct by_asset;
    /**
     * @ingroup object_index
     */
    typedef multi_index_container<
        skyStreet_object,
        indexed_by<
            ordered_unique< tag<by_id>, member< object, object_id_type, &object::id > >,
            ordered_non_unique< tag<by_asset>,member< skyStreet_object, asset, &skyStreet_object::on_chain_amount > >
        >
    > skyStreet_object_multi_index_type;
    
    /**
     * @ingroup object_index
     */
    typedef generic_index<skyStreet_object, skyStreet_object_multi_index_type> skyStreet_index;
}}

FC_REFLECT_ENUM(graphene::chain::skyStreet_object::ExchangeType,
                (Sell)
                (Buy))

FC_REFLECT_ENUM(graphene::chain::skyStreet_object::DeliveryType,
                (SellPrior)
                (Normal))

FC_REFLECT_ENUM(graphene::chain::skyStreet_object::ExchangeQuantityType,
                (Multi)
                (Single))

FC_REFLECT_ENUM(graphene::chain::skyStreet_object::GoodType,
                (OnChain)
                (OffChain))

FC_REFLECT_DERIVED( graphene::chain::skyStreet_object,
                    (graphene::db::object),
                    (exchange_type)
                    (delivery_type)
                    (exchange_quantity_type)
                    (good_type)
                    (seller)
                    (buyer)
                    (on_chain_amount)
                    (amount)
                    (sub_sky_street_object)
                    (description)
                    (extras)
                    )

