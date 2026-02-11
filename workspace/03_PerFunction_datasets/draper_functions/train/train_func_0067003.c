nm_inotify_helper_add_watch (NMInotifyHelper *self, const char *path)
{
	NMInotifyHelperPrivate *priv = NM_INOTIFY_HELPER_GET_PRIVATE (self);
	int wd;
	guint32 refcount;

	g_return_val_if_fail (priv->ifd >= 0, -1);


	wd = inotify_add_watch (priv->ifd, path, IN_CLOSE_WRITE);
	if (wd < 0)
		return -1;

	refcount = GPOINTER_TO_UINT (g_hash_table_lookup (priv->wd_refs, GINT_TO_POINTER (wd)));
	refcount++;
	g_hash_table_replace (priv->wd_refs, GINT_TO_POINTER (wd), GUINT_TO_POINTER (refcount));

	return wd;
}
