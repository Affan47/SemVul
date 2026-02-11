e_radio_action_get_current_action (GtkRadioAction *radio_action)
{
	GSList *group;
	gint current_value;

	g_return_val_if_fail (GTK_IS_RADIO_ACTION (radio_action), NULL);

	group = gtk_radio_action_get_group (radio_action);
	current_value = gtk_radio_action_get_current_value (radio_action);

	while (group != NULL) {
		gint value;

		radio_action = GTK_RADIO_ACTION (group->data);
		g_object_get (radio_action, "value", &value, NULL);

		if (value == current_value)
			return radio_action;

		group = g_slist_next (group);
	}

	return NULL;
}
