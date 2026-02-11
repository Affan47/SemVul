pk_progress_set_percentage (PkProgress *progress, gint percentage)
{
	g_return_val_if_fail (PK_IS_PROGRESS (progress), FALSE);


	if (progress->priv->percentage == percentage)
		return FALSE;


	progress->priv->percentage = percentage;
	g_object_notify (G_OBJECT(progress), "percentage");

	return TRUE;
}
