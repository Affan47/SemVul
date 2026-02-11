nation_set_should_attack()
{
	err_when( id != MSG_NATION_SET_SHOULD_ATTACK );

	short *shortPtr = (short *)data_buf;

	err_when( *shortPtr != remote.nation_processing );
	if( !nation_array.is_deleted(*shortPtr) && !nation_array.is_deleted(shortPtr[1]) )
	{
#ifdef DEBUG_LONG_LOG
		long_log->printf("nation %d %s instruct attack nation %d\n", shortPtr[0],
			shortPtr[2] ? "set":"clear", shortPtr[1]);
#endif
		nation_array[shortPtr[0]]->set_relation_should_attack(shortPtr[1], (char)shortPtr[2], COMMAND_REMOTE);
	}
}
