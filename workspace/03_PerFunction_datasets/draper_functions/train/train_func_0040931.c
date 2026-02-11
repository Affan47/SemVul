camel_folder_change_info_clear (CamelFolderChangeInfo *info)
{
	struct _CamelFolderChangeInfoPrivate *p;

	g_return_if_fail (info != NULL);

	p = info->priv;

	g_ptr_array_set_size (info->uid_added, 0);
	g_ptr_array_set_size (info->uid_removed, 0);
	g_ptr_array_set_size (info->uid_changed, 0);
	g_ptr_array_set_size (info->uid_recent, 0);
	if (p->uid_source) {
		g_hash_table_destroy (p->uid_source);
		p->uid_source = NULL;
	}
	g_hash_table_destroy (p->uid_stored);
	p->uid_stored = g_hash_table_new (g_str_hash, g_str_equal);
	g_ptr_array_set_size (p->uid_filter, 0);
	camel_mempool_flush (p->uid_pool, TRUE);
}
