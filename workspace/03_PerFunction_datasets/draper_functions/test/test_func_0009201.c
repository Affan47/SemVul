project_name_desc(GtkDialog *w, gint response_id, GtkEntry **entries)
{
	const char *name, *desc;
	GttProject *proj;
	GttProject *sib_prj;

	if (GTK_RESPONSE_OK != response_id)
	{
		gtk_widget_destroy (GTK_WIDGET (w));
		return;
	}

	sib_prj = gtt_projects_tree_get_selected_project (projects_tree);

	if (!(name = gtk_entry_get_text(entries[0]))) return;
	if (!(desc = gtk_entry_get_text(entries[1]))) return;
	if (!name[0]) return;


	proj = gtt_project_new_title_desc(name, desc);
	gtt_project_insert_after (proj, sib_prj);
	gtt_projects_tree_append_project (projects_tree, proj, gtt_project_get_parent (sib_prj));

	gtk_widget_destroy (GTK_WIDGET (w));
}
