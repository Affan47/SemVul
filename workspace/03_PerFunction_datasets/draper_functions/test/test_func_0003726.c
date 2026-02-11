totem_action_toggle_aspect_ratio (TotemObject *totem)
{
	GtkAction *action;
	int tmp;

	tmp = totem_action_get_aspect_ratio (totem);
	tmp++;
	if (tmp > BVW_RATIO_DVB)
		tmp = BVW_RATIO_AUTO;

	action = gtk_action_group_get_action (totem->main_action_group, "aspect-ratio-auto");
	gtk_radio_action_set_current_value (GTK_RADIO_ACTION (action), tmp);
}
