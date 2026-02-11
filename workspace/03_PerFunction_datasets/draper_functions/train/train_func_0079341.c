gpk_modal_dialog_run (GpkModalDialog *dialog)
{
	g_return_val_if_fail (GPK_IS_CLIENT_DIALOG (dialog), FALSE);


	if (g_main_loop_is_running (dialog->priv->loop))
		g_main_loop_quit (dialog->priv->loop);

	dialog->priv->response = GTK_RESPONSE_NONE;
	g_main_loop_run (dialog->priv->loop);

	return dialog->priv->response;
}
