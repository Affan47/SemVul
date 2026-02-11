skip_build_ship()
{
	err_when( id != MSG_F_HARBOR_SKIP_SHIP );

	short *shortPtr = (short *)data_buf;
	if( validate_firm(*shortPtr) )
	{

		FirmHarbor *harbor = firm_array[*shortPtr]->cast_to_FirmHarbor();
		if(!harbor)
		{
			err_here();
		}
		else
		{
#ifdef DEBUG_LONG_LOG
			long_log->printf("harbr %d skip ship building\n", shortPtr[0]);
#endif
			harbor->cancel_build_unit();
		}
	}
}
