units_return_camp()
{
	err_when( id != MSG_UNITS_RETURN_CAMP );

	short *shortPtr = (short *)data_buf;
	validate_selected_unit_array(shortPtr+1, *shortPtr);

	if( *shortPtr > 0)
	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("return to camp, units : ");
		for(int i = 0; i < *shortPtr; ++i)
		{
			long_log->printf("%d,", shortPtr[1+i]);
			if( i % 20 == 19)
				long_log->printf("\n");
		}
		long_log->printf("\n");
#endif
		unit_array.return_camp(COMMAND_REMOTE, shortPtr+1, *shortPtr);
	}
}
