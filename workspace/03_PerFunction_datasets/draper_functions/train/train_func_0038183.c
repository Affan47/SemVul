unit_burn()
{
	err_when( id != MSG_UNIT_BURN);

	short *shortPtr = (short *)data_buf;
	short unitCount =1;
	validate_selected_unit_array(shortPtr, unitCount);

	if( unitCount > 0 )
	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("unit %d burn at (%d,%d)\n", shortPtr[0], shortPtr[1], shortPtr[2]);
#endif
		unit_array[*shortPtr]->burn(shortPtr[1], shortPtr[2], COMMAND_REMOTE);
	}
}
