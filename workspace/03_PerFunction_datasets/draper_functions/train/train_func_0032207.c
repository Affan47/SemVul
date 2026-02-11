log_msg(char *message) {
    FILE    *log = 0;
    struct stat status;
    char str_time[30];

    if (stat(logfname, &status) >= 0){
	log = fopen(logfname, "a");
	if (log==NULL) return(1);
	sprintf(str_time,"%s",ctime(&pres_time)+3);
	str_time[strlen(str_time)-1]=0;

        fprintf(log, "%s - %s\n",str_time,message);
	fclose(log);
    	return(0);
    }
}
