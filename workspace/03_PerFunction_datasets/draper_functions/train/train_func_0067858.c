save_argv(void)
{
	unsigned int i;

	for (i = 0; i < oldargc; i++)
		free(oldargv[i]);
	oldargc = newargc;
	newargc = 0;
	for (i = 0; i < oldargc; i++) {
		oldargv[i] = newargv[i];
		newargv[i] = NULL;
	}
}
