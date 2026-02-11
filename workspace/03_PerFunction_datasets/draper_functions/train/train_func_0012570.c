real_load (gchar **search_path, const gchar *culture, const gchar *name, gboolean refonly)
{
	MonoAssembly *result = NULL;
	gchar **path;
	gchar *filename;
	const gchar *local_culture;
	gint len;

	if (!culture || *culture == '\0') {
		local_culture = "";
	} else {
		local_culture = culture;
	}

	filename =  g_strconcat (name, ".dll", NULL);
	len = strlen (filename);

	for (path = search_path; *path; path++) {
		if (**path == '\0')
			continue;


		strcpy (filename + len - 4, ".dll");
		if (try_load_from (&result, *path, local_culture, "", filename, refonly))
			break;


		strcpy (filename + len - 4, ".exe");
		if (try_load_from (&result, *path, local_culture, "", filename, refonly))
			break;


		strcpy (filename + len - 4, ".dll");
		if (try_load_from (&result, *path, local_culture, name, filename, refonly))
			break;


		strcpy (filename + len - 4, ".exe");
		if (try_load_from (&result, *path, local_culture, name, filename, refonly))
			break;
	}

	g_free (filename);
	return result;
}
