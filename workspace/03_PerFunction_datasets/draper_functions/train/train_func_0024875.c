shell_set_note_from_entry(ShellModuleEntry * entry)
{
    if (entry->notefunc) {
	const gchar *note = module_entry_get_note(entry);

	if (note) {
	    gtk_label_set_markup(GTK_LABEL(shell->note->label), note);
	    gtk_widget_show(shell->note->frame);
	} else {
	    gtk_widget_hide(shell->note->frame);
	}
    } else {
	gtk_widget_hide(shell->note->frame);
    }
}
