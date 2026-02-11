sub_cnc_error_cb (G_GNUC_UNUSED GdaThreadWrapper *wrapper, G_GNUC_UNUSED GdaConnection *sub_cnc,
		  G_GNUC_UNUSED const gchar *signal,
		  gint n_param_values, const GValue *param_values, G_GNUC_UNUSED gpointer gda_reserved,
		  GdaConnection *wrapper_cnc)
{
	GdaConnectionEvent *ev;
	g_assert (n_param_values == 1);
	ev = g_value_get_object (param_values);
	g_object_ref (ev);
	gda_connection_add_event (wrapper_cnc, ev);
}
