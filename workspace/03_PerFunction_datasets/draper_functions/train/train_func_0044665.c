show_controls_action_callback (GtkToggleAction *action, Totem *totem)
{
	gboolean show;

	show = gtk_toggle_action_get_active (action);


	if (show)
		totem->controls_visibility = TOTEM_CONTROLS_VISIBLE;
	else
		totem->controls_visibility = TOTEM_CONTROLS_HIDDEN;

	show_controls (totem, FALSE);
}
