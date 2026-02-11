option_cache (struct option_cache **oc, struct data_string *dp,
		  struct expression *expr, struct option *option,
		  const char *file, int line)
{
	if (!option_cache_allocate (oc, file, line))
		return 0;
	if (dp)
		data_string_copy (&(*oc) -> data, dp, file, line);
	if (expr)
		expression_reference (&(*oc) -> expression, expr, file, line);
	option_reference(&(*oc)->option, option, MDL);
	return 1;
}
