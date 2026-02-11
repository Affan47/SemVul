e_date_edit_check_time_changed (EDateEdit *dedit)
{
	EDateEditPrivate *priv;
	GtkWidget *child;
	const gchar *time_text;
	struct tm tmp_tm;
	gboolean none = FALSE, valid = TRUE, time_changed;

	priv = dedit->priv;

	tmp_tm.tm_hour = 0;
	tmp_tm.tm_min = 0;

	child = gtk_bin_get_child (GTK_BIN (priv->time_combo));
	time_text = gtk_entry_get_text (GTK_ENTRY (child));
	if (field_set_to_none (time_text))
		none = TRUE;
	else if (!e_date_edit_parse_time (dedit, time_text, &tmp_tm))
		valid = FALSE;

	time_changed = e_date_edit_set_time_internal (
		dedit, valid, none,
		tmp_tm.tm_hour,
		tmp_tm.tm_min);

	if (time_changed) {
		e_date_edit_update_time_entry (dedit);
		g_signal_emit (dedit, signals[CHANGED], 0);
	}
}
