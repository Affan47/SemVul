cf_create_default_path_string( char *path, uint path_max, int pathtype, char *filename, bool localize )
{
#ifdef SCP_UNIX
	if ( filename && strpbrk(filename,"/")  ) {
#else
	if ( filename && strpbrk(filename,"/\\:")  ) {
#endif

		strncpy( path, filename, path_max );

	} else {
		cf_root *root = cf_get_root(0);

		if (!root) {
			Assert( filename != NULL );
			strncpy(path, filename, path_max);
			return 1;
		}

		Assert(CF_TYPE_SPECIFIED(pathtype));


		if ( (pathtype == CF_TYPE_PLAYERS) || (pathtype == CF_TYPE_SINGLE_PLAYERS) || (pathtype == CF_TYPE_MULTI_PLAYERS) ) {
			strncpy(path, Pilot_file_path, path_max);
		} else {
			strncpy(path, root->path, path_max);
		}

		strcat_s(path, path_max, Pathtypes[pathtype].path);


		if (Pathtypes[pathtype].path[0] != '\0') {
			if ( path[strlen(path)-1] != DIR_SEPARATOR_CHAR ) {
				strcat_s(path, path_max, DIR_SEPARATOR_STR);
			}
		}


		if (filename) {
			strcat_s(path, path_max, filename);


			if (localize) {

				char path_tmp[MAX_PATH_LEN] = { 0 };
				strncpy( path_tmp, path, MAX_PATH_LEN - 1 );


				if(lcl_add_dir_to_path_with_filename(path_tmp, MAX_PATH_LEN - 1)) {

					FILE *fp = fopen(path, "rb");
					if (fp) {
						fclose(fp);
						return 1;
					}
				}
			}
		}
	}

	return 1;
}
