sub_cnc_closed_cb (G_GNUC_UNUSED GdaThreadWrapper *wrapper, G_GNUC_UNUSED GdaConnection *sub_cnc,
		   G_GNUC_UNUSED const gchar *signal, G_GNUC_UNUSED gint n_param_values,
		   G_GNUC_UNUSED const GValue *param_values, G_GNUC_UNUSED gpointer gda_reserved,
		   GdaConnection *wrapper_cnc)
{
	ThreadConnectionData *cdata;
	cdata = _gda_thread_connection_get_data (wrapper_cnc);
	if (!cdata)
		return;
	cdata->sub_connection_has_closed = TRUE;
}
