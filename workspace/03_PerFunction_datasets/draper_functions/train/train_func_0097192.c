fontRowChanged(void)
{
	static char szFontFamily[60];
	GtkTreeSelection *selection;
	GtkTreeModel *model;
	GtkTreeIter iter;
	gchar *text;

	model = gtk_tree_view_get_model(GTK_TREE_VIEW(m_fontList));
	selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(m_fontList));
	if ( gtk_tree_selection_get_selected (selection, &model, &iter) )
	{
		gtk_tree_model_get(model, &iter, TEXT_COLUMN, &text, -1);
		g_snprintf(szFontFamily, 50, "%s",text);
		g_free(text), text = NULL;
		addOrReplaceVecProp("font-family",static_cast<gchar*>(szFontFamily));
	}

	updatePreview();
}
