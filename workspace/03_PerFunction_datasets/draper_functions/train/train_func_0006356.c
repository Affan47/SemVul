GetNextFile(nffile_t *nffile, time_t twin_start, time_t twin_end) {
static int cnt;


	if ( nffile ) {
		CloseFile(nffile);
		current_file = NULL;
	} else {

		cnt  = 0;
	}


	if ( file_list.num_strings == cnt ) {
		current_file = NULL;
		return EMPTY_LIST;
	}


	while ( cnt < file_list.num_strings ) {
#ifdef DEVEL
		printf("Process: '%s'\n", file_list.list[cnt] ? file_list.list[cnt] : "<stdin>");
#endif
		nffile = OpenFile(file_list.list[cnt], nffile);
		if ( !nffile ) {
			return NULL;
		}
		current_file = file_list.list[cnt];
		cnt++;


		if ( nffile->fd == STDIN_FILENO ) {
			current_file = NULL;
			return nffile;
		}

		if ( CheckTimeWindow(twin_start, twin_end, nffile->stat_record) ) {

			return nffile;
		}
		CloseFile(nffile);
	}

	current_file = NULL;
	return EMPTY_LIST;

}
