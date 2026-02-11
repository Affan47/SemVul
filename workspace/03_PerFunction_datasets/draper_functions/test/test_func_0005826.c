data_rqdump(void){
	dump_time.tv_sec = last_dump.tv_sec +
	                   config[CF_DUMP_INTER].valeur.integer;
	dump_time.tv_usec = last_dump.tv_usec;
	if(dump_time.tv_sec < 0){
			dump_time.tv_sec = 0;
			dump_time.tv_usec = 0;
	}
}
