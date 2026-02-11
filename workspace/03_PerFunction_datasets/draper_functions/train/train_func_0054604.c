caravan_set_stop()
{
	err_when( id != MSG_U_CARA_SET_STOP );

	short *shortPtr = (short *)data_buf;
	short unitCount =1;
	validate_selected_unit_array(shortPtr, unitCount);

	if( unitCount > 0)
	{
		Unit *unitPtr = unit_array[*shortPtr];
		UnitCaravan *caravanPtr;
		if( unitPtr->unit_id != UNIT_CARAVAN)
		{
			err_here();
		}
		else
		{
#ifdef DEBUG_LONG_LOG
			long_log->printf("caravan %d set stop %d at (%d,%d)\n", shortPtr[0], shortPtr[1], shortPtr[2], shortPtr[3]);
#endif
			caravanPtr = (UnitCaravan *)unitPtr;
			caravanPtr->set_stop(shortPtr[1], shortPtr[2], shortPtr[3], COMMAND_REMOTE);


		}
	}
}
