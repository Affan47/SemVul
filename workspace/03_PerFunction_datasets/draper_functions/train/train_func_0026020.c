hdup_cp(char *from, char *to)
{
	int pid, status;
	char *command;


	if ( from == NULL || to == NULL )
		return 1;

	command = g_strdup_printf("/bin/cp -f %s %s 2>/dev/null", from, to);

	if ((pid = fork()) < 0) {
		perror("fork");
		hdup_cleanup(1,NULL);
	}
	if ( pid == 0 ) {

		execl("/bin/sh", "sh", "-c",
				command,
				(char *)NULL);
		hdup_cleanup(1,NULL);
	}

	while (wait(&status) != pid)
		 ;

	if ( status != 0 ) {

		LOG("%s %s %s %s", "Could not perform the copy:", from, "to", to );
		return 1;
	}
	return 0;
}
