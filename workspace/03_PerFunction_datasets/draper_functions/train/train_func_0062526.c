spy_assassinate()
{
	err_when( id != MSG_SPY_ASSASSINATE );


	short *shortPtr = (short *)data_buf;
	if( !spy_array.is_deleted(*shortPtr) )
	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("spy %d assassinate unit %d", shortPtr[0], shortPtr[1]);
#endif
		spy_array[*shortPtr]->assassinate( shortPtr[1], COMMAND_REMOTE );
	}
}
