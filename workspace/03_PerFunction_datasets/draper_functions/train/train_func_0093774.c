glob3(GDir *dir, gchar *pattern, gchar *pattern_last, wapi_glob_t *pglob,
      size_t *limitp, gboolean ignorecase, gboolean unique)
{
	const gchar *name;


	while ((name = g_dir_read_name(dir))) {
		if (!match(name, pattern, pattern + strlen (pattern),
			   ignorecase)) {
			continue;
		}
		if (!unique ||
		    !contains (pglob, name)) {
			globextend (name, pglob, limitp);
		}
	}

	return(0);
}
