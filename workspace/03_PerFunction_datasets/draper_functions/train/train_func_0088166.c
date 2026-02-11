split_version(const char *uri)
{
	int *retv = g_malloc0(4 * sizeof(int));
	char **sp = g_strsplit(uri, ".", 4);
	int i;
	for (i = 0; i < 4 && sp[i]; i++)
	{
		retv[i] = atoi(sp[i]);
	}
	g_strfreev(sp);
	return retv;
}
