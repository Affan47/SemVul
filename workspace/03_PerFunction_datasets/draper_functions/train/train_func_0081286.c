openlogdir(char *logdir)
{
	DIR *dp = NULL;
	struct dirent *dirp = NULL;
	int fdate, ffirst = 0, state = 0;
	char fname[128];
	char *current = NULL;

	if ((dp = opendir(logdir)) == NULL) {
		printf("Can't open %s dir\n", logdir);
		exit(-1);
	}

        printf("Current %d-%d-%d\n",  cur_year, cur_month, cur_day);


	while((dirp = readdir(dp)) != NULL) {
		if ((dirp->d_name[0] == '@')) {
			if ((timeconvert(dirp->d_name, 128, cur_year, cur_month, cur_day, &fdate)) > 0 ) {
				printf("today file: %.128s  ", dirp->d_name);
				printf("date %d : \n", fdate);
				if(state == 0) {
					ffirst = fdate;
					strncpy(fname, dirp->d_name, 128);
					state = 1;
				}
				else if(fdate < ffirst) {
					ffirst = fdate;
					strncpy(fname, dirp->d_name, 128);
				}
			}
		}
	}
	if ((chdir(logdir)) == -1) {
		fprintf(stderr, "chdir  %s\n",  strerror(errno));
		exit(-1);
	}
	rewinddir(dp);
	while((dirp = readdir(dp)) != NULL) {
		if (dirp->d_name[0] == '@'){
			if ((timeconvert(dirp->d_name, 128, cur_year, cur_month, cur_day, &fdate)) > 0 ) {
				if ((strncmp(fname, dirp->d_name, 128)) != 0)
					readQmailLogFile(dirp->d_name);
			}
		}
	}
	closedir(dp);

	if (ffirst != 0)
		readSpecialLogFile(fname, cur_year, cur_month, cur_day);
	current = (char *)malloc((strlen(logstore) + 10) * sizeof(char));
	sprintf(current, "%s/current", logstore);
	readSpecialLogFile(current, cur_year, cur_month, cur_day);
}
