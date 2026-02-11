version_compare(char *filename, int *u_major, int *u_minor, int *u_build, int *l_major, int *l_minor, int *l_build)
{
	int usr_major, usr_minor, usr_build;
	int latest_major, latest_minor, latest_build;


	FILE *f = fopen(filename, "rt");
	if (f == NULL) {
		return -1;
	}


	char buffer[MAX_LINE_LENGTH+1] = {0};
	char verbuffer[MAX_LINE_LENGTH+1] = {0};

	while ( !feof(f) ) {

		fgets(buffer, MAX_LINE_LENGTH, f);


		if (buffer[0] != '\0' && buffer[strlen(buffer) - 1] == '\n')
			buffer[strlen(buffer) - 1] = 0;


		if (buffer[0] == '\0') continue;


		if (buffer[0] == VERSION_FILE_COMMENT_CHAR) continue;


		strcpy_s(verbuffer, buffer);
	}
	fclose(f);


	if (verbuffer[0] == '\0') {

		return -1;
	}


	latest_major = 0;
	latest_minor = 0;
	latest_build = 0;

	if (sscanf(verbuffer, "%i %i %i", &latest_major, &latest_minor, &latest_build) != 3) {

		return -1;
	}


	usr_major = os_config_read_uint("Version", "Major", 0);
	usr_minor = os_config_read_uint("Version", "Minor", 0);
	usr_build = os_config_read_uint("Version", "Build", 0);


	if ( VER(usr_major, usr_minor, usr_build) == 0 ) {

		return NO_VERSION_IN_REGISTRY;
	}


	if(u_major != NULL){
		*u_major = usr_major;
	}
	if(u_minor != NULL){
		*u_minor = usr_minor;
	}
	if(u_build != NULL){
		*u_build = usr_build;
	}
	if(l_major != NULL){
		*l_major = latest_major;
	}
	if(l_minor != NULL){
		*l_minor = latest_minor;
	}
	if(l_build != NULL){
		*l_build = latest_build;
	}


	if (VER(usr_major, usr_minor, usr_build) < VER(latest_major, latest_minor, latest_build)) {
		return 0;
	}


	return 1;
}
