stickynotes_remove(StickyNote *note)
{
	GtkBuilder *builder;
	GtkWidget *dialog;

	builder = gtk_builder_new ();
	gtk_builder_add_from_file (builder, BUILDER_PATH, NULL);

	dialog = GTK_WIDGET (gtk_builder_get_object (builder, "delete_dialog"));

	gtk_window_set_transient_for(GTK_WINDOW(dialog), GTK_WINDOW(note->w_window));

	if (stickynote_get_empty(note)
	    || !gconf_client_get_bool(stickynotes->gconf, GCONF_PATH "/settings/confirm_deletion", NULL)
	    || gtk_dialog_run(GTK_DIALOG(dialog)) == GTK_RESPONSE_OK) {
		stickynote_free(note);


		stickynotes->notes = g_list_remove(stickynotes->notes, note);


		stickynotes_applet_update_tooltips();


		stickynotes_save();
	}

	gtk_widget_destroy(dialog);
	g_object_unref(builder);
}
