user_deletesieve(const char *user)
{
    const char *sieve_path;
    char filename[2048];
    DIR *mbdir;
    struct dirent *next = NULL;


    if(config_getswitch(IMAPOPT_SIEVEUSEHOMEDIR)) return 0;

    sieve_path = user_sieve_path(user);

    mbdir = opendir(sieve_path);

    if (mbdir) {
	while((next = readdir(mbdir)) != NULL) {
	    if (!strcmp(next->d_name, ".")
	        || !strcmp(next->d_name, "..")) continue;

	    snprintf(filename, sizeof(filename), "%s/%s",
		     sieve_path, next->d_name);

	    unlink(filename);
	}

	closedir(mbdir);


	rmdir(sieve_path);
    }

    return 0;
}
