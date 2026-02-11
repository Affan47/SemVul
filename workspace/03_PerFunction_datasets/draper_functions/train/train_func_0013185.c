find_in_dir (DIR *current, const gchar *name)
{
	struct dirent *entry;

#ifdef DEBUG
	g_message ("%s: looking for [%s]\n", __func__, name);
#endif

	while((entry = readdir (current)) != NULL) {
#ifdef DEBUGX
		g_message ("%s: found [%s]\n", __func__, entry->d_name);
#endif

		if (!g_ascii_strcasecmp (name, entry->d_name)) {
			char *ret;

#ifdef DEBUG
			g_message ("%s: matched [%s] to [%s]\n", __func__,
				   entry->d_name, name);
#endif

			ret = g_strdup (entry->d_name);
			closedir (current);
			return ret;
		}
	}

#ifdef DEBUG
	g_message ("%s: returning NULL\n", __func__);
#endif

	closedir (current);

	return(NULL);
}
