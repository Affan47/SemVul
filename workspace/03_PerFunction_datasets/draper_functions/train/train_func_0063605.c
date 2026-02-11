get_file_args(char *filename, argv_buf *abp, argv_buf *xabp)
{
    argv_stack stck;
    int i;
    char **argv;

    ARGV_STACK_INIT(&stck);

    i = 0;
    argv = read_args_file(filename);

    while (argv) {

	while (argv[i]) {
	    if (strcmp(argv[i], "-args_file") == 0) {
		char **new_argv;
		char *fname;
		if (!argv[++i])
		    usage("-args_file");
		fname = argv[i++];
		new_argv = read_args_file(fname);
		if (new_argv) {
		    if (argv[i])
			push_argv(&stck, argv, i);
		    else
			efree(argv);
		    i = 0;
		    argv = new_argv;
		}
	    }
	    else {
		if (strcmp(argv[i], "-extra") == 0) {
		    i++;
		    while (argv[i])
			save_arg(xabp, argv[i++]);
		    break;
		}
		save_arg(abp, argv[i++]);
	    }
	}

	efree(argv);

	pop_argv(&stck, &argv, &i);
    }
}
