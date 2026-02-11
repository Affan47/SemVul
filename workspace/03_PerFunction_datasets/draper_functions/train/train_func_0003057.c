RFG_Regions_add( RFG_Regions* regions, uint32_t regionId,
                                 const char* regionName,
                                 const char* defaultGroupName )
{
  RFG_RegionInfoHN* region_info_hn;

  if( !regions )
    return NULL;

  if( !regionName || *regionName == '\0' )
  {
    fprintf( stderr, "RFG_Regions_add(): Error: Empty region name\n" );
    return NULL;
  }

  if( !defaultGroupName || *defaultGroupName == '\0' )
  {
    fprintf( stderr, "RFG_Regions_add(): Error: Empty default group name\n" );
    return NULL;
  }


  region_info_hn = region_info_hash_get( regions->region_infos, regionId );


  if( !region_info_hn )
  {
    char*    group_name = NULL;
    int32_t  call_limit;
    uint32_t stack_bounds[2];
    uint8_t  flags;


    if( !RFG_Groups_get( regions->groups, regionName, &group_name ) )
      return NULL;


    if( !group_name )
      group_name = (char*)defaultGroupName;


    if( !RFG_Filter_getRegionRules( regions->filter, regionName, group_name,
          &call_limit, stack_bounds, &flags ) )
    {
      return NULL;
    }


    region_info_hn =
      region_info_hash_put( regions->region_infos, regionId, regionName,
        group_name, call_limit, stack_bounds, flags );
    regions->num_region_infos++;
  }

  return &(region_info_hn->info);
}
