G__env_name(int n)
{
    int i;

    read_env(G_VAR_GISRC);
    if (n >= 0)
	for (i = 0; i < count; i++)
	    if (env[i].name && *env[i].name && (n-- == 0))
		return env[i].name;
    return NULL;
}
