url_params_get(const url_params_t *up, const char *name)
{
	g_assert(up != NULL);
	g_assert(up->params != NULL);

	return htable_lookup(up->params, name);
}
