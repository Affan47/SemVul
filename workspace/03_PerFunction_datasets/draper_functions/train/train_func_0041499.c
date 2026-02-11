editor_destroy (ERuleEditor *editor,
                GObject *deadbeef)
{
	if (editor->edit) {
		g_object_unref (editor->edit);
		editor->edit = NULL;
	}

	editor->dialog = NULL;

	gtk_widget_set_sensitive (GTK_WIDGET (editor), TRUE);
	e_rule_editor_set_sensitive (editor);
}
