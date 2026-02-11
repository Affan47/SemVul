handleKeyValueList( const uint32_t & proc, OTF_KeyValueList * kvs )
{

   uint32_t keys_num = OTF_KeyValueList_getCount( kvs );

   if( keys_num > 0 )
   {

      static const TokenFactoryScopeI * tkfac_defkeyval =
         theTokenFactory->getScope( DEF_REC_TYPE__DefKeyValue );

      for( uint32_t i = 0; i < keys_num; i++ )
      {


         OTF_KeyValuePair* pair = 0;
         OTF_KeyValueList_getPairByIndex( kvs, i, &pair );
         vt_assert( pair );


         uint32_t global_key = tkfac_defkeyval->translate( proc, pair->key );
         vt_assert( global_key != 0 );
         pair->key = global_key;
      }
   }
}
