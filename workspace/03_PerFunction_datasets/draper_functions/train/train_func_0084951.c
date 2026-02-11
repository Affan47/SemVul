pk_notify_finalize (GObject *object)
{
	PkNotify *notify;

	g_return_if_fail (object != NULL);
	g_return_if_fail (PK_IS_NOTIFY (object));
	notify = PK_NOTIFY (object);


	if (notify->priv->timeout_id != 0) {
		g_source_remove (notify->priv->timeout_id);
	}

	G_OBJECT_CLASS (pk_notify_parent_class)->finalize (object);
}
