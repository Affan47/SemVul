secondary_pixbuf_toggled (GtkWidget        *widget,
			GladeEntryEditor *entry_editor)
{
	if (entry_editor->loading || !entry_editor->loaded_widget)
		return;

	if (!gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON (entry_editor->secondary_pixbuf_radio)))
		return;

	entry_editor->modifying = TRUE;

	glade_command_push_group (_("Setting %s to use a secondary icon from filename"), entry_editor->loaded_widget->name);
	set_pixbuf_mode (entry_editor, FALSE);
	glade_command_pop_group ();

	entry_editor->modifying = FALSE;


	glade_editable_load (GLADE_EDITABLE (entry_editor),
			     entry_editor->loaded_widget);
}
