focus_to_custom (GtkToggleButton *togglebutton, ZoomState *state)
{
	if (gtk_toggle_button_get_active (togglebutton))
		gtk_widget_grab_focus (GTK_WIDGET (&state->zoom->entry));
}
