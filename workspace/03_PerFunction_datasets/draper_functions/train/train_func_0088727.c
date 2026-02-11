camel_folder_change_info_change_uid (CamelFolderChangeInfo *info,
                                     const gchar *uid)
{
	struct _CamelFolderChangeInfoPrivate *p;
	GPtrArray *olduids;
	gchar *olduid;

	g_return_if_fail (info != NULL);
	g_return_if_fail (uid != NULL);

	p = info->priv;

	if (g_hash_table_lookup_extended (p->uid_stored, uid, (gpointer) &olduid, (gpointer) &olduids)) {

		return;
	}

	olduid = camel_mempool_strdup (p->uid_pool, uid);
	g_ptr_array_add (info->uid_changed, olduid);
	g_hash_table_insert (p->uid_stored, olduid, info->uid_changed);
}
