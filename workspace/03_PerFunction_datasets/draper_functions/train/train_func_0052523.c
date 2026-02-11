open_files(int signal) {
    if(log_file_path) {
        if(log_fp) fclose(log_fp);
        log_fp=fopen(log_file_path,"a");
        if(log_fp==NULL) perror("fopen");
        setvbuf(log_fp,NULL,_IONBF,0);
        if(signal>0)
            logprintf(MY_NAME,"Got signal %d, reopened log file\n",signal);
    } else {
        log_fp=stderr;
    }
    if(dribble_path) {
        if(dribble_fd>=-1) close(dribble_fd);
        dribble_fd=open(dribble_path,O_WRONLY|O_CREAT|O_APPEND,0600);
        if(dribble_fd==-1)
            logprintf(MY_NAME,"Cannot open dribble file %s",dribble_path);
    }
}
