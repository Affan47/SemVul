chirp_reli_bulkio( struct chirp_bulkio *v, int count, time_t stoptime )
{
	INT64_T delay=0;
	INT64_T nexttry;
	INT64_T result;
	time_t current;

	while(1) {
		result = chirp_reli_bulkio_once(v,count,stoptime);

		if(result>=0 || errno!=ECONNRESET) return result;

		if(time(0)>=stoptime) {
			errno = ECONNRESET;
			return -1;
		}
		if(delay>=2) debug(D_NOTICE,"couldn't connect: still trying...\n");
		current = time(0);
		nexttry = MIN(stoptime,current+delay);
		debug(D_CHIRP,"try again in %d seconds\n",nexttry-current);
		sleep_until(nexttry);
		if(delay==0) {
			delay = 1;
		} else {
			delay = MIN(delay*2,MAX_DELAY);
		}
	}
}
