_e2_confdlg_focus_out_cb (GtkWidget *widget, GdkEventFocus *event,
	gpointer data)
{
	if (cancel_blocked)
	{
		g_signal_handlers_unblock_by_func (G_OBJECT (config_dialog),
			e2_dialog_key_neg_cb, config_dialog);
		cancel_blocked = FALSE;
	}
	return FALSE;
}
