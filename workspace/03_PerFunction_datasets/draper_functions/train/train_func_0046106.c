find_subr(int *index, const char *name)
{
	if (*index < 0)
		*index = RESERVED_find_subr(name, strlen(name));
}
