rmuserfunc(char *name)
{
	long index;

	index = findstr(&funcnames, name);
	if (index < 0) {
		warning("No function named \"%s\" to be undefined", name);
		return;
	}
	if (functions[index] == NULL) {
		warning("No defined function \"%s\" to be undefined", name);
		return;
	}
	freenumbers(functions[index]);
	free(functions[index]);
	if ((inputisterminal() && conf->resource_debug & RSCDBG_STDIN_FUNC) ||
	    (!inputisterminal() && conf->resource_debug & RSCDBG_FILE_FUNC))
		printf("%s() undefined\n", name);
	functions[index] = NULL;
}
