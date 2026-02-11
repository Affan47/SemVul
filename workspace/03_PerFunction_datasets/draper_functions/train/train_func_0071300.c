__instw_printdirent64(struct dirent64 *entry) {

	if(entry!=NULL) {
		debug(	4,
			"entry(%p) {\n"
			"\td_ino     : %" PRId64 "\n"
			"\td_off     : %" PRId64 "d\n"
			"\td_reclen  : %d\n"
			"\td_type    : %d\n"
			"\td_name    : \"%.*s\"\n",
			entry,
			entry->d_ino,
			D_OFF(entry->d_off),
			entry->d_reclen,
			(int)entry->d_type,
			(int)entry->d_reclen,(char*)(entry->d_name)
			);
	} else {
		debug(	4,"entry(null) \n");
	}

	return 0;
}
