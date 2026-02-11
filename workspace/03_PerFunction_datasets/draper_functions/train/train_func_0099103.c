item_queue_is_blocked_by_file (TrackerMinerFS *fs,
                               GFile *file)
{
	g_return_val_if_fail (G_IS_FILE (file), FALSE);

	if (fs->priv->item_queue_blocker != NULL &&
	    (fs->priv->item_queue_blocker == file ||
	     g_file_equal (fs->priv->item_queue_blocker, file))) {
		return TRUE;
	}

	return FALSE;
}
