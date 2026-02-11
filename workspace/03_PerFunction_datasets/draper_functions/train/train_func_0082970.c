load_god_info()
{
	GodRec  *godRec;
	GodInfo *godInfo;
	int      i;
	Database *dbGod = game_set.open_db(GOD_DB);

	god_count      = (short) dbGod->rec_count();
	god_info_array = (GodInfo*) mem_add( sizeof(GodInfo)*god_count );


	memset( god_info_array, 0, sizeof(GodInfo) * god_count );

	for( i=0 ; i<god_count ; i++ )
	{
		godRec  = (GodRec*) dbGod->read(i+1);
		godInfo = god_info_array+i;

		godInfo->god_id = i+1;

		godInfo->race_id = misc.atoi(godRec->race_id, godRec->RACE_ID_LEN);
		godInfo->unit_id = misc.atoi(godRec->unit_id, godRec->UNIT_ID_LEN);

		godInfo->exist_pray_points = misc.atoi(godRec->exist_pray_points, godRec->PRAY_POINTS_LEN);
		godInfo->power_pray_points = misc.atoi(godRec->power_pray_points, godRec->PRAY_POINTS_LEN);

		godInfo->can_cast_power   = godRec->can_cast_power == '1';
		godInfo->cast_power_range = misc.atoi(godRec->cast_power_range, godRec->CAST_POWER_RANGE_LEN);
	}
}
