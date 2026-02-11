pfs_poll_init()
{
	int i;
	for(i=0;i<POLL_TABLE_MAX;i++) {
		poll_table[i].pid = -1;
	}
	for(i=0;i<SLEEP_TABLE_MAX;i++) {
		sleep_table[i].pid = -1;
	}
}
