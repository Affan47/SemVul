totem_action_show_help (TotemObject *totem)
{
	GError *error = NULL;

	if (gtk_show_uri (gtk_widget_get_screen (totem->win), "help:totem", gtk_get_current_event_time (), &error) == FALSE) {
		totem_action_error (totem, _("Totem could not display the help contents."), error->message);
		g_error_free (error);
	}
}
