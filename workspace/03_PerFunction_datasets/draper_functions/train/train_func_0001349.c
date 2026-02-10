cfile_init(char *exe_dir, char *cdrom_dir)
{
	int i;


	encrypt_init();

	if ( !cfile_inited ) {
		char buf[CFILE_ROOT_DIRECTORY_LEN];

		cfile_inited = 1;

		memset(buf, 0, CFILE_ROOT_DIRECTORY_LEN);
		strncpy(buf, exe_dir, CFILE_ROOT_DIRECTORY_LEN - 1);
		i = strlen(buf);


		if(cfile_in_root_dir(buf)){
			MessageBox((HWND)NULL, "FreeSpace2/Fred2 cannot be run from a drive root directory!", "Error", MB_OK);
			return 1;
		}

		while (i--) {
			if (buf[i] == DIR_SEPARATOR_CHAR){
				break;
			}
		}

		if (i >= 2) {
			buf[i] = 0;
			cfile_chdir(buf);
		} else {
			MessageBox((HWND)NULL, "Error trying to determine executable root directory!", "Error", MB_OK);
			return 1;
		}


		strncpy(Cfile_root_dir, buf, CFILE_ROOT_DIRECTORY_LEN-1);
#ifdef SCP_UNIX
		snprintf(Cfile_user_dir, CFILE_ROOT_DIRECTORY_LEN-1, "%s/%s/", detect_home(), Osreg_user_dir);
#endif

		for ( i = 0; i < MAX_CFILE_BLOCKS; i++ ) {
			Cfile_block_list[i].type = CFILE_BLOCK_UNUSED;
		}


		cf_chksum_long_init();

		Cfile_cdrom_dir = cdrom_dir;
		cf_build_secondary_filelist(Cfile_cdrom_dir);

		atexit( cfile_close );
	}

	return 0;
}
