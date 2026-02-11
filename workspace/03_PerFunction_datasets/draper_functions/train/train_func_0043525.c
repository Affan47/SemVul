e_send_options_get_widgets_data (ESendOptionsDialog *sod)
{
	ESendOptionsDialogPrivate *priv;
	ESendOptionsGeneral *gopts;
	ESendOptionsStatusTracking *sopts;

	priv = sod->priv;
	gopts = sod->data->gopts;
	sopts = sod->data->sopts;

	gopts->priority = gtk_combo_box_get_active ((GtkComboBox *) priv->priority);
	gopts->security = gtk_combo_box_get_active ((GtkComboBox *) priv->security);

	gopts->reply_enabled = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->reply_request));
	gopts->reply_convenient = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->reply_convenient));
	gopts->reply_within = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (priv->within_days));

	gopts->expiration_enabled = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->expiration));
	gopts->expire_after = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON (priv->expire_after));
	gopts->delay_enabled = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->delay_delivery));

	if (e_date_edit_date_is_valid (E_DATE_EDIT (priv->delay_until)) &&
								e_date_edit_time_is_valid (E_DATE_EDIT (priv->delay_until)))
		gopts->delay_until = e_date_edit_get_time (E_DATE_EDIT (priv->delay_until));

	sopts->tracking_enabled = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->create_sent));

	sopts->autodelete = gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->autodelete));

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->delivered)))
		sopts->track_when = E_DELIVERED;
	else if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (priv->delivered_opened)))
		sopts->track_when = E_DELIVERED_OPENED;
	else
		sopts->track_when = E_ALL;

	sopts->opened = gtk_combo_box_get_active ((GtkComboBox *) priv->when_opened);
	sopts->accepted = gtk_combo_box_get_active ((GtkComboBox *) priv->when_accepted);
	sopts->declined = gtk_combo_box_get_active ((GtkComboBox *) priv->when_declined);
	sopts->completed = gtk_combo_box_get_active ((GtkComboBox *) priv->when_completed);
}
