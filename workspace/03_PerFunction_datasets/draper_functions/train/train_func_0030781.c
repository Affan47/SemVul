init()
{


	reachable_region_count=0;

	for( int seaRegionId=1 ; seaRegionId<=region_array.region_info_count ; seaRegionId++ )
	{
		if( region_array[seaRegionId]->region_type != REGION_SEA )
			continue;

		if( !region_array.is_adjacent(region_id, seaRegionId) )
			continue;


		RegionStat* regionStat = region_array.region_stat_array;

		for( int i=1 ; i<=region_array.region_stat_count ; i++, regionStat++ )
		{
			if( regionStat->region_id==region_id )
				continue;

			if( region_array.is_adjacent(seaRegionId, regionStat->region_id) )
			{
				reachable_region_array[reachable_region_count].sea_region_id  = seaRegionId;
				reachable_region_array[reachable_region_count].land_region_stat_id = i;

				if( ++reachable_region_count == MAX_REACHABLE_REGION_PER_STAT )
					return;
			}
		}
	}
}
