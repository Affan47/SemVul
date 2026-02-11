flag_is_empty(const bitflag *flags, const size_t size)
{
	size_t i;

	for (i = 0; i < size; i++)
		if (flags[i] > 0) return FALSE;

	return TRUE;
}
