attachment_update_icon_column (EAttachment *attachment)
{
	g_mutex_lock (&attachment->priv->idle_lock);

	if (attachment->priv->update_icon_column_idle_id == 0) {
		guint idle_id;

		idle_id = g_idle_add_full (
			G_PRIORITY_HIGH_IDLE,
			attachment_update_icon_column_idle_cb,
			e_weak_ref_new (attachment),
			(GDestroyNotify) e_weak_ref_free);
		attachment->priv->update_icon_column_idle_id = idle_id;
	}

	g_mutex_unlock (&attachment->priv->idle_lock);
}
