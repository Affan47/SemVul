gda_quark_list_remove (GdaQuarkList *qlist, const gchar *name)
{
	gboolean removed = FALSE;
	g_return_if_fail (qlist != NULL);
	g_return_if_fail (name != NULL);

	if (qlist->hash_table && g_hash_table_remove (qlist->hash_table, name))
		removed = TRUE;
	if (!removed && qlist->hash_protected)
		g_hash_table_remove (qlist->hash_protected, name);
}
