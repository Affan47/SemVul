brasero_data_disc_import_session_cb (GtkToggleAction *action,
				     BraseroDataDisc *self)
{
	BraseroDataDiscPrivate *priv;
	BraseroMedium *medium;
	gboolean res;

	priv = BRASERO_DATA_DISC_PRIVATE (self);

	medium = g_object_get_data (G_OBJECT (action), BRASERO_DATA_DISC_MEDIUM);
	if (!medium)
		return;

	brasero_notify_message_remove (priv->message, BRASERO_NOTIFY_CONTEXT_MULTISESSION);
	res = brasero_data_disc_import_session (self,
						medium,
						gtk_toggle_action_get_active (action));


	if (gtk_toggle_action_get_active (action) != res) {
		g_signal_handlers_block_by_func (action, brasero_data_disc_import_session_cb, self);
		gtk_toggle_action_set_active (GTK_TOGGLE_ACTION (action), res);
		g_signal_handlers_unblock_by_func (action, brasero_data_disc_import_session_cb, self);
	}
}
