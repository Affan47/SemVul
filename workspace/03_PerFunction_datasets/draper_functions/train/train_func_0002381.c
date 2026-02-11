camel_text_index_rename (const gchar *old,
                         const gchar *new)
{
	gchar *oldname, *newname;
	gsize oldname_len, newname_len;
	gint err;


	oldname_len = strlen (old) + 12;
	newname_len = strlen (new) + 12;
	oldname = alloca (oldname_len);
	newname = alloca (newname_len);
	g_snprintf (oldname, oldname_len, "%s.index", old);
	g_snprintf (newname, newname_len, "%s.index", new);

	if (g_rename (oldname, newname) == -1 && errno != ENOENT)
		return -1;

	g_snprintf (oldname, oldname_len, "%s.index.data", old);
	g_snprintf (newname, newname_len, "%s.index.data", new);

	if (g_rename (oldname, newname) == -1 && errno != ENOENT) {
		err = errno;
		g_snprintf (oldname, oldname_len, "%s.index", old);
		g_snprintf (newname, newname_len, "%s.index", new);
		g_rename (newname, oldname);
		errno = err;
		return -1;
	}

	return 0;
}
