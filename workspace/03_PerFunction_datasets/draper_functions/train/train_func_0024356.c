debris_find_oldest()
{
	int		oldest_index;
	fix		oldest_time;
	debris	*db;

	oldest_index = -1;
	oldest_time = 0x7fffffff;

	for ( db = GET_FIRST(&Hull_debris_list); db != END_OF_LIST(&Hull_debris_list); db = GET_NEXT(db) ) {
		if ( (db->time_started < oldest_time) && !(Objects[db->objnum].flags & OF_SHOULD_BE_DEAD) ) {
			oldest_index = DEBRIS_INDEX(db);
			oldest_time = db->time_started;
		}
	}

	return oldest_index;
}
