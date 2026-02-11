do_final_quest(void)
{
	if(quest_killdb) {
		aFree(quest_killdb);
		quest_killdb = NULL;
		max_killdb_count = 0;
	}

	return 0
;
}
