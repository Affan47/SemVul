magnet_resource_set_string(const char **p, const char *str)
{
	const char *atom;

	g_return_if_fail(p);
	g_return_if_fail(str);

	atom = atom_str_get(str);
	atom_str_free_null(p);
	*p = atom;
}
