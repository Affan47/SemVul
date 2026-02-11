_env_array_putenv(const char *string)
{
	int rc = 0;
	char name[256], *value;

	value = xmalloc(ENV_BUFSIZE);
	if ((_env_array_entry_splitter(string, name, sizeof(name),
				       value, ENV_BUFSIZE)) &&
	    (setenv(name, value, 1) != -1))
		rc = 1;

	xfree(value);
	return rc;
}
