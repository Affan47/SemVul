on_treeview_row_activated (GtkTreeView *view, GtkTreePath *arg1,
                           GtkTreeViewColumn *arg2,
                           SymbolDBPlugin *plugin)
{
	GtkTreeModel *model;
	GtkTreeSelection *selection;
	GtkTreeIter iter;
	IAnjutaDocumentManager *docman;
	GFile* file;
	gchar *filename, *full_path;
	gint line;

	AnjutaShell *shell = ANJUTA_PLUGIN (plugin)->shell;
	selection = gtk_tree_view_get_selection (view);
	if (!gtk_tree_selection_get_selected (selection, &model, &iter))
	    return;

	gtk_tree_model_get (model, &iter,
	                    SYMBOL_DB_MODEL_PROJECT_COL_FILE, &filename,
	                    SYMBOL_DB_MODEL_PROJECT_COL_LINE, &line,
	                    -1);
	g_return_if_fail (filename != NULL);

	docman = anjuta_shell_get_interface (shell, IAnjutaDocumentManager,
	                                     NULL);
	g_return_if_fail (docman != NULL);

	full_path = g_build_filename (plugin->project_root_dir, filename, NULL);
	file = g_file_new_for_path (full_path);
	ianjuta_document_manager_goto_file_line (docman, file, line, NULL);
	g_free (full_path);
	g_free (filename);
	g_object_unref (file);

	if (IANJUTA_IS_MARKABLE (plugin->current_editor))
	{
		ianjuta_markable_delete_all_markers (IANJUTA_MARKABLE (plugin->current_editor),
		                                     IANJUTA_MARKABLE_LINEMARKER,
		                                     NULL);

		ianjuta_markable_mark (IANJUTA_MARKABLE (plugin->current_editor),
		                       line, IANJUTA_MARKABLE_LINEMARKER, NULL, NULL);
	}
}
