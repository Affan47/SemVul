pbx_substitute_variables_helper(struct ast_channel *c, const char *cp1, char *cp2, int count)
{
	size_t used;
	pbx_substitute_variables_helper_full(c, (c) ? ast_channel_varshead(c) : NULL, cp1, cp2, count, &used);
}
