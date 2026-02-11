execv ( const char *command, char * const argv[] ) {
	struct command *cmd;
	int argc;
	int rc;


	for ( argc = 0 ; argv[argc] ; argc++ ) {}


	if ( command == NULL ) {
		rc = 0;
		goto done;
	}


	if ( argc == 0 ) {
		DBG ( "%s: empty argument list\n", command );
		rc = -EINVAL;
		goto done;
	}


	reset_getopt();


	for_each_table_entry ( cmd, COMMANDS ) {
		if ( strcmp ( command, cmd->name ) == 0 ) {
			rc = cmd->exec ( argc, ( char ** ) argv );
			goto done;
		}
	}

	printf ( "%s: command not found\n", command );
	rc = -ENOEXEC;

 done:

	if ( rc ) {
		errno = rc;
		if ( errno < 0 )
			errno = -errno;
	}

	return rc;
}
