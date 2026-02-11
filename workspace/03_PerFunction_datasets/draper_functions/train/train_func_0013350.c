module_load(const char *path, char **prefixes)
{
	char *exppath, *name, *submodule, *rootmodule;
        int start, end, ret;

	g_return_val_if_fail(path != NULL, FALSE);

	exppath = convert_home(path);

	name = module_get_name(exppath, &start, &end);
	rootmodule = module_get_root(name, prefixes);
	submodule = module_get_sub(name, rootmodule);
	g_free(name);

	ret = module_load_full(exppath, rootmodule, submodule,
			       start, end, prefixes);

	g_free(rootmodule);
	g_free(submodule);
        g_free(exppath);
        return ret;
}
