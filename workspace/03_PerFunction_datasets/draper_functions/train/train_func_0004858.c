read_var(const char *var)
{
	struct git_var *ptr;
	const char *val;
	val = NULL;
	for (ptr = git_vars; ptr->read; ptr++) {
		if (strcmp(var, ptr->name) == 0) {
			val = ptr->read(IDENT_ERROR_ON_NO_NAME);
			break;
		}
	}
	return val;
}
