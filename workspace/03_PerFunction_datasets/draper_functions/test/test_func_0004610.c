rivers_open_files(char *spool_dir_name, river *rivers)
{
	DIR* spool_dir;
	struct dirent* pde;

	spool_dir = opendir( spool_dir_name );

	if ( spool_dir == NULL ) {
		perror( spool_dir_name );
		return 0;
	}

	if (chdir(spool_dir_name) != 0) {
		perror(spool_dir_name);
		return 0;
	}

	while( (pde = readdir( spool_dir )) ) {
		unsigned int idx;
		for (idx = 0; idx < NUM_RIVERS; idx++) {
			river *r = &rivers[idx];
			if (strncmp(pde->d_name, r->input_prefix, strlen(r->input_prefix)) == 0)
				if (! open_streams(pde->d_name, r))
					return 0;
		}
	}

	closedir(spool_dir);

	return 1;
}
