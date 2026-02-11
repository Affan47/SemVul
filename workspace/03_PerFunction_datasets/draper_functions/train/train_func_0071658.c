localcmd(int argc UNUSED_PARAM, char **argv)
{
	char *name;

	argv = argptr;
	while ((name = *argv++) != NULL) {
		mklocal(name);
	}
	return 0;
}
