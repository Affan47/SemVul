pfs_poll_wakein( struct timeval tv )
{
	struct sleep_entry *s;
	int i;

	debug(D_POLL,"wake in time %d.%06d",tv.tv_sec,tv.tv_usec);

	for(i=0;i<SLEEP_TABLE_MAX;i++) {
		s = &sleep_table[i];
		if(s->pid<0) {
			s->pid = pfs_process_getpid();
			gettimeofday(&s->stoptime,0);
			s->stoptime.tv_sec += tv.tv_sec;
			s->stoptime.tv_usec += tv.tv_usec;
			while(s->stoptime.tv_usec>1000000) {
				s->stoptime.tv_sec++;
				s->stoptime.tv_usec-=1000000;
			}
			if(i>=sleep_table_size) sleep_table_size=i+1;
			return;
		}
	}

	fatal("ran out of sleep table space!");
}
