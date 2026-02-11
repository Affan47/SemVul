RFG_Regions_dup( const RFG_Regions* oldRegions )
{
  RFG_Regions* ret = RFG_Regions_init();

  if( ret )
  {
    uint32_t i;


    if( oldRegions->num_region_infos > 0 )
    {
      for( i = 0; i < REGION_INFO_HASH_MAX; i++ )
      {
        RFG_RegionInfoHN* curr = oldRegions->region_infos[i];
        while( curr )
        {
          region_info_hash_put( ret->region_infos, curr->info.regionId,
            curr->info.regionName, curr->info.groupName, curr->info.callLimit,
            curr->info.stackBounds, curr->info.flags );
          ret->num_region_infos++;

          curr = curr->next;
        }
      }
    }


    if( oldRegions->num_cpath_infos > 0 )
    {
      for( i = 0; i < CPATH_INFO_HASH_MAX; i++ )
      {
        RFG_CallPathInfoHN* curr = oldRegions->cpath_infos[i];
        while( curr )
        {
          cpath_info_hash_put( ret->cpath_infos, curr->info.hash,
            curr->info.size, curr->info.regionIds, curr->info.callLimit );
          ret->num_cpath_infos++;

          curr = curr->next;
        }
      }
    }
  }

  return ret;
}
