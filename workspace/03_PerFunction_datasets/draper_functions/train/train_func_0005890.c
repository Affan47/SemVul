evt_row_deleted(GtkTreeModel *model, GtkTreePath *path, gpointer user)
{
	P_CmdSeq	*page = user;
	CmdSeq		*cs;
	GtkTreeIter	csiter, riter;
	gboolean	valid;
	GList		*rows = NULL;

	if((cs = cmdseq_get_selected(page, &csiter)) == NULL)
		return;


	for(valid = gtk_tree_model_get_iter_first(GTK_TREE_MODEL(page->dstore), &riter);
	    valid;
	    valid = gtk_tree_model_iter_next(GTK_TREE_MODEL(page->dstore), &riter))
	{
		CmdRow	*row;
		gtk_tree_model_get(GTK_TREE_MODEL(page->dstore), &riter, DEF_COLUMN_ROW, &row, -1);
		rows = g_list_append(rows, row);
	}
	csq_cmdseq_rows_relink(cs, rows);
}
