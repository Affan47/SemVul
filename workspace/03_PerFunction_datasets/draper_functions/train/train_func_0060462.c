evt_duprow_clicked(GtkWidget *wid, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdSeq		*cs;
	GtkTreeIter	riter;
	CmdRow		*row, *nr;
	GtkTreePath	*path;

	if((cs = cmdseq_get_selected(page, NULL)) == NULL)
		return;
	if((row = cmdrow_get_selected(page, &riter)) == NULL)
		return;

	if((nr = csq_cmdrow_copy(row)) != NULL)
	{
		csq_cmdseq_row_append(cs, nr);
		gtk_list_store_append(page->dstore, &riter);
		gtk_list_store_set(page->dstore, &riter,
					DEF_COLUMN_TYPE, csq_cmdrow_type_to_string(nr->type),
					DEF_COLUMN_DEF,  nr->def->str,
					DEF_COLUMN_ROW,  nr,
					-1);
		gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(page->dview)), &riter);
		if((path = gtk_tree_model_get_path(GTK_TREE_MODEL(page->dstore), &riter)) != NULL)
		{
			gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(page->dview), path, NULL, TRUE, 0.5f, 0.5f);
			gtk_tree_path_free(path);
		}
		page->modified = TRUE;
	}
}
