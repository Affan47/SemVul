slayer_server_parse_args(int argc, char **argv,slayer_http_server_t *server) {
	int i;
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-' && strlen(argv[i]) == 2) {
			char *extra_arg = i+1 < argc && argv[i+1][0] != '-' ? argv[i+1] : NULL;
		switch (argv[i][1]) {
		  case '?':
			  fprintf(stdout,"Usage %s:  [-t thread-count -p port -h ip-to-bind-to -d debug -w socket-timeout -b basedir -l logfile -e error-logfile -n number-of-stats-buckets [defaults to 1 bucket per minute for 24 hours] -i interval-to-update-stats-buckets [ defaults to 60 seconds] ] -v [prints version and exits]\n",basename(argv[0]));
			  for(i = 0; i < server->service_map_size; i++) {
				  fprintf(stdout,"\t %s\n",server->service_map[i]->service->help_string);
			  }
			  exit(0);
		  case 'b':
			  server->basedir = extra_arg;
			  break;
		  case 'd':
			  server->debug = extra_arg;
			  break;
		  case 'e':
			  server->elogfile = extra_arg;
			  break;
		  case 'h':
			  server->hostname = extra_arg;
			  break;
		  case 'l':
			  server->logfile = extra_arg ;
			  break;
		  case 'p':
			  server->port = atoi(extra_arg);
			  break;
		  case 't':
			  server->thread_count = atoi(extra_arg);
			  break;
		  case 'w':
			  server->socket_timeout = (atoi(extra_arg) == 0 ? 10 : atoi(extra_arg)) * 1000 * 1000;
			  break;
		  case 'n':
			  server->nslice = (atoi(extra_arg) == 0 ? 60*24 : atoi(extra_arg)) ;
			  break;
		  case 'i':
			  server->tslice = (atoi(extra_arg) == 0 ? 60 : atoi(extra_arg)) ;
			  break;
		  case 'v':
			  fprintf(stdout,"%s\n",server->server_name);
			  exit(0);
		  default:
			  break;
		  }
		}
	}
	if ( server->thread_count == 0 || server->port == 0 ) {
		fprintf(stdout,"Usage %s:  [-t thread-count -p port -h ip-to-bind-to -d debug -w socket-timeout -b basedir -l logfile -e error-logfile -n number-of-stats-buckets [defaults to 1 bucket per minute for 24 hours] -i interval-to-update-stats-buckets [ defaults to 60 seconds] ] -v [prints version and exits]\n",basename(argv[0]));
		for(i = 0; i < server->service_map_size; i++) {
			fprintf(stdout,"\t %s\n",server->service_map[i]->service->help_string);
		}
		exit(0);
	}
}
