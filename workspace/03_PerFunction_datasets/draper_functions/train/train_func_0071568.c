camp_patrol()
{
	err_when( id != MSG_F_CAMP_PATROL);
	if( validate_firm(*(short *)data_buf) )
	{
		FirmCamp *camp = firm_array[*(short *)data_buf]->cast_to_FirmCamp();
		if(camp)
		{
			if(camp->overseer_recno || camp->worker_count > 0)
			{
#ifdef DEBUG_LONG_LOG
				long_log->printf("camp %d patrols\n", *(short *)data_buf);
#endif
				camp->patrol();
			}
		}
		else
		{
			err_here();
		}
	}
}
