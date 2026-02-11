evt_add_clicked(GtkWidget *wid, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdSeq		*ns;
	GtkTreeIter	iter;
	GtkTreePath	*path;

	if((ns = csq_cmdseq_new(csq_cmdseq_unique_name(page->cmdseq), 0UL)) == NULL)
		return;
	csq_cmdseq_hash(&page->cmdseq, ns);
	gtk_list_store_append(page->store, &iter);
	gtk_list_store_set(page->store, &iter,
				CMDSEQ_COLUMN_NAME, ns->name,
				CMDSEQ_COLUMN_CMDSEQ, ns,
				-1);
	gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(page->view)), &iter);
	path = gtk_tree_model_get_path(GTK_TREE_MODEL(page->store), &iter);
	gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(page->view), path, NULL, TRUE, 0.5f, 0.0f);
	gtk_tree_path_free(path);

	gtk_editable_select_region(GTK_EDITABLE(page->name), 0, -1);
	gtk_widget_grab_focus(page->name);
}
