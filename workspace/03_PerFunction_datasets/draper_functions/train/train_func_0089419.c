imapx_command_run_sync (CamelIMAPXServer *is,
                        CamelIMAPXCommand *ic,
                        GCancellable *cancellable,
                        GError **error)
{
	guint cancel_id = 0;
	gboolean success = TRUE;


	g_warn_if_fail (ic->complete == NULL);
	ic->complete = imapx_command_complete;

	if (G_IS_CANCELLABLE (cancellable))
		cancel_id = g_cancellable_connect (
			cancellable,
			G_CALLBACK (imapx_command_cancelled),
			camel_imapx_command_ref (ic),
			(GDestroyNotify) camel_imapx_command_unref);


	camel_imapx_command_ref (ic);

	imapx_command_queue (is, ic);

	camel_imapx_command_wait (ic);

	if (cancel_id > 0)
		g_cancellable_disconnect (cancellable, cancel_id);

	if (camel_imapx_command_set_error_if_failed (ic, error))
		return FALSE;

	return success;
}
