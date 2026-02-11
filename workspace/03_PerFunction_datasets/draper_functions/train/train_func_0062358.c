getoptarg(int *argcp, char ***argvp)
{
	int argc = *argcp;
	char **argv = *argvp;
	if(argv[1][2] != 0)
		return &argv[1][2];
	if(argc<=2 || argv[2][0]=='-')
		error("incomplete option %s", argv[1]);
	*argcp = argc-1;
	*argvp = ++argv;
	return argv[1];
}
