on_scan_files_end_1 (AnjutaLauncher * launcher, int child_pid,
				   int exit_status, gulong time_taken_in_seconds,
				   gpointer user_data)
{
	SymbolDBEngine *dbe = (SymbolDBEngine *) user_data;
	SymbolDBEnginePriv *priv;

	g_return_if_fail (user_data != NULL);

	priv = dbe->priv;

	DEBUG_PRINT ("***** ctags ended (%s) (%s) *****", priv->ctags_path,
	    priv->cnc_string);

	if (priv->shutting_down == TRUE)
		return;

	priv->ctags_path = NULL;
}
