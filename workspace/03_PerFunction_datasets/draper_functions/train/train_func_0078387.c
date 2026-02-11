get_array_length_alt(char *name, char *s, int *two_dim, long entry_size)
{
	int retval;

	retval = get_array_length(s, two_dim, entry_size);
	if (retval)
		retval = builtin_array_length(name, retval, two_dim);
	return retval;
}
