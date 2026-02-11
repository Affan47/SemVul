pk_package_id_split (const gchar *package_id)
{
	gchar **sections = NULL;

	if (package_id == NULL)
		goto out;


	sections = g_strsplit (package_id, ";", -1);
	if (g_strv_length (sections) != 4)
		goto out;


	if (sections[0][0] != '\0')
		return sections;
out:
	g_strfreev (sections);
	return NULL;
}
