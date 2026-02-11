cfg_error(char *name, int number)
{
	if (john_main_process)
		fprintf(stderr, "Error in %s at line %d\n",
		    path_expand(name), number);
	error();
}
