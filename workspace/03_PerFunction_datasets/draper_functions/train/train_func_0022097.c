ship_del_stop()
{
	err_when( id != MSG_U_SHIP_DEL_STOP );

	short *shortPtr = (short *)data_buf;
	short unitCount =1;
	validate_selected_unit_array(shortPtr, unitCount);

	if( unitCount > 0)
	{
		Unit *unitPtr = unit_array[*shortPtr];
		UnitMarine *shipPtr;
		if( unitPtr->sprite_info->sprite_sub_type != 'M')
		{
			err_here();
		}
		else
		{
#ifdef DEBUG_LONG_LOG
			long_log->printf("ship %d delete stop %d\n", shortPtr[0], shortPtr[1]);
#endif
			shipPtr = (UnitMarine *)unitPtr;
			shipPtr->del_stop(shortPtr[1], COMMAND_REMOTE);
		}
	}
}
