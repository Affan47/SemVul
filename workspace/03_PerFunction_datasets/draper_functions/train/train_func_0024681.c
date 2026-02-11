parse_url_subst_dist(void) {
	DIR *dirfd=NULL;
	struct dirent *info=NULL;
	static char retbuf[128]="unknown";
	char *buf;


	dirfd=opendir("/etc/.");
	while ((info=readdir(dirfd)) != NULL) {
		if ((buf=strstr(info->d_name,"-version"))!=NULL) {
			buf[0]=0;
			strncpy(retbuf, info->d_name, sizeof(retbuf));
			return(retbuf);
		}
		if ((buf=strstr(info->d_name,"_version"))!=NULL) {
			buf[0]=0;
			strncpy(retbuf, info->d_name, sizeof(retbuf));
			return(retbuf);
		}
		if ((buf=strstr(info->d_name,"-release"))!=NULL) {
			buf[0]=0;
			strncpy(retbuf, info->d_name, sizeof(retbuf));
			return(retbuf);
		}
	}


	return(retbuf);
}
