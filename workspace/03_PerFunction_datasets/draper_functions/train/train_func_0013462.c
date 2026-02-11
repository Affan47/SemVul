alloc_string_def(char **sptr, const char *start, const char *end,
		 const char *def)
{
    if (end == start)
	return alloc_string(sptr, def, NULL);
    else
	return alloc_string(sptr, start, end);
}
