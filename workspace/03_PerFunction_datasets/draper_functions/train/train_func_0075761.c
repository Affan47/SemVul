parse_arguments(int argc, char *argv[])
{


	package = strrchr(argv[0], '/');
	if (package == 0)
		package = argv[0];
	else
		package++;

	if (argc==2) {
		if( !strcmp( argv[1], "quit" ) ) {
			notify_type = JackSessionSaveAndQuit;
			return;
		}
	}
	if (argc==3) {
		if( !strcmp( argv[1], "save" ) ) {
			notify_type = JackSessionSave;
			save_path = argv[2];
			return;
		}

	}
	fprintf(stderr, "usage: %s quit|save [path]\n", package);
	exit(9);
}
