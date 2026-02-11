G__getenv2(const char *name, int loc)
{
    if (strcmp(name, "GISBASE") == 0)
	return getenv(name);

    read_env(loc);

    return get_env(name, loc);
}
