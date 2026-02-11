optimize_town_race()
{
	RegionStat* regionStat = region_array.region_stat_array;

	for( int i=0 ; i<region_array.region_stat_count ; i++, regionStat++ )
	{
		if( regionStat->town_nation_count_array[nation_recno-1] > 0 )
			optimize_town_race_region( regionStat->region_id );
	}
}
