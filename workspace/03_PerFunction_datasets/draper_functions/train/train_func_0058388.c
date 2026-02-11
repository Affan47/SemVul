execute_task(ITEM now, ITEM item) {
#ifdef _WIN32
	char start[300];
	sprintf(start, "start %s", item.command);

	log_task("START", item.command);

	printf ( "%02d.%02d %02d:%02d\tCOMMAND:\t%s\n", now.monthday, now.month, now.hour, now.minute, item.command );
    system(start);

	log_task("STOP", item.command);

#else
    pid_t child_pid=fork();
	int status;
	switch(child_pid) {
		case -1:

			printf ( "Unable to start process (%s).\n", item.command );
			exit(EXIT_FAILURE);
		case 0:

			log_task("START", item.command);

            int sys_exit=system(item.command);

			log_task("STOP", item.command);

            exit(sys_exit);
		default:

			printf ( "%03d.%02d %02d:%02d\tCOMMAND:\t%s\n", now.monthday, now.month, now.hour, now.minute, item.command );
			child_pid = wait(&status);

			if ( WIFEXITED(status) != 0 ) {

			} else {
				printf ( "Child (%d) has been finished with  error %d.\n", child_pid, WEXITSTATUS(status) );
			}
    }
#endif
}
