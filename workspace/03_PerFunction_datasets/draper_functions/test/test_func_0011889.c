cb_c_fmt_dialog_chooser_check_page (CFormatState *state, gchar const *name,
				    gint page)
{
	GtkWidget *w = go_gtk_builder_get_widget (state->gui, name);

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (w)))
		return (1 << page);
	else
		return 0;
}
