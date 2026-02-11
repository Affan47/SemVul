log_pid_file(file_name)
    const char *file_name;
{
    struct stat status;
    FILE *file;


    if (stat(file_name, &status) == 0 && S_ISREG(status.st_mode)) {
	syslog(LOG_NOTICE, "warning: the PID file already exists: %s",
	    file_name);
    }


    file = fopen(file_name, "w");
    if (file == NULL) {
	syslog(LOG_ERR, "failed to open the file, %s: %s", strerror(errno),
	    file_name);
	goto failed;
    }


    fprintf(file, "%d\n", (int)getpid());
    if (ferror(file)) {
	syslog(LOG_ERR, "failed to write to the file, %s: %s", strerror(errno),
	    file_name);
	goto failed;
    }


    if (fclose(file) == EOF) {
	syslog(LOG_ERR, "failed to close the file, %s: %s", strerror(errno),
	    file_name);
	file = NULL;
	goto failed;
    }

    syslog(LOG_DEBUG, "debug: write a PID to the file: %s", file_name);
    return 0;


  failed:
    if (file != NULL && fclose(file) == EOF) {
	syslog(LOG_ERR, "failed to close the file, %s: %s", strerror(errno),
	    file_name);
    }
    syslog(LOG_ERR, "failed to write a PID to the file: %s", file_name);
    return -1;
}
