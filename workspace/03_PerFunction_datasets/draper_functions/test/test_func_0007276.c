STRING_extend(char *str, int new_len)
{
	STRING *sstr;

	if (!str)
	{
		sstr = alloc_string(new_len);
		#ifdef DEBUG_ME
			fprintf(stderr, "STRING_extend: NULL -> %p / %p\n", str, str->data);
		#endif
	}
	else
	{
		sstr = realloc_string(STRING_from_ptr(str), new_len);
		#ifdef DEBUG_ME
			fprintf(stderr, "STRING_extend: %p / %p -> %p / %p\n", STRING_from_ptr(*ptr), *ptr, str, str->data);
		#endif
	}

	return sstr ? sstr->data : NULL;
}
