ve_get_first_working_command (const char *list,
			      gboolean only_existance)
{
	int i;
	char **vector;
	char *ret = NULL;

	if (list == NULL)
		return NULL;

	vector = g_strsplit (list, ";", -1);
	for (i = 0; vector[i] != NULL; i++) {
		if (ve_first_word_executable (vector[i],
					      only_existance)) {
			ret = g_strdup (vector[i]);
			break;
		}
	}
	g_strfreev (vector);
	return ret;
}
