unlink_recursive(const char *truepath) {
	int rcod;
	struct stat trueinfo;
	DIR *wdir;
	struct dirent *went;
	char wpath[PATH_MAX+1];
	struct stat winfo;

#if DEBUG
	debug(2,"unlink_recursive(%s)\n",truepath);
#endif

	rcod=true_lstat(truepath,&trueinfo);
	if(rcod<0 && errno!=ENOENT) return -1;
	if(rcod!=0) return 0;

	if(S_ISDIR(trueinfo.st_mode)) {
		wdir=true_opendir(truepath);
		if(wdir==NULL) return -1;
		while((went=true_readdir(wdir))!=NULL) {

			if( 	went->d_name[0]=='.' &&
				(	(went->d_name[1]=='\0') ||
					(	went->d_name[1]=='.' &&
						went->d_name[2]=='\0') ) )
				{ continue; }


			strcpy(wpath,truepath);
			strcat(wpath,"/");
			strcat(wpath,went->d_name);
			rcod=true_lstat(wpath,&winfo);
			if(rcod!=0) {
				closedir(wdir);
				return -1;
			}

			if(S_ISDIR(winfo.st_mode)) {
				unlink_recursive(wpath);
				true_rmdir(wpath);
			} else {
				true_unlink(wpath);
			}
		}
		closedir(wdir);
		true_rmdir(truepath);
	} else {
		true_unlink(truepath);
	}

	return rcod;
}
