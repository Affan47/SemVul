pk_package_id_equal_fuzzy_arch (const gchar *package_id1, const gchar *package_id2)
{
	gchar **sections1;
	gchar **sections2;
	gboolean ret = FALSE;

	sections1 = pk_package_id_split (package_id1);
	sections2 = pk_package_id_split (package_id2);
	if (g_strcmp0 (sections1[0], sections2[0]) == 0 &&
	    g_strcmp0 (sections1[1], sections2[1]) == 0 &&
	    pk_package_id_equal_fuzzy_arch_section (sections1[2], sections2[2]))
		ret = TRUE;

	g_strfreev (sections1);
	g_strfreev (sections2);
	return ret;
}
