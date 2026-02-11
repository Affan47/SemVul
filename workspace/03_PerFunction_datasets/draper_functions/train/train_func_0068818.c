db_debug(const char *s)
{
    if (debug_on)
	fprintf(stderr, "debug(%s): %s\n", who ? who : "", s ? s : "<NULL>");
}
