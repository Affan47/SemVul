check_fileending(struct dirent const *entry, char *fileending) {
	struct stat buf;
	char *end;


        if(stat(entry->d_name,&buf)) {
        	perror("couldn't get stats for file");
	}


        if(S_ISREG(buf.st_mode) && (end=strrchr(entry->d_name,'.'))!=NULL){

		if(!strcmp(end,fileending)) {
                       	return -1;
		}
	}

        return 0;
}
