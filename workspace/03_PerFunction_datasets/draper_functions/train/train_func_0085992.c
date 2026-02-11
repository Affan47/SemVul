_populateCList(void)
{
	const PD_Style * pStyle;
	const gchar *org_name, *loc_name;

	size_t nStyles = getDoc()->getStyleCount();
	xxx_UT_DEBUGMSG(("DOM: we have %d styles\n", nStyles));

	if (m_listStyles == NULL) {
		m_listStyles = gtk_list_store_new(2, G_TYPE_STRING, G_TYPE_STRING);
		GtkTreeModel *sort = gtk_tree_model_sort_new_with_model (GTK_TREE_MODEL (m_listStyles));
		gtk_tree_sortable_set_sort_column_id (GTK_TREE_SORTABLE (sort), 0, GTK_SORT_ASCENDING);
		gtk_tree_view_set_model (GTK_TREE_VIEW(m_tvStyles), sort);
		g_object_unref (G_OBJECT (sort));
		g_object_unref (G_OBJECT (m_listStyles));
	} else {
		gtk_list_store_clear (m_listStyles);
	}

	GtkTreeViewColumn *column = gtk_tree_view_get_column (GTK_TREE_VIEW(m_tvStyles), 0);
	if (!column)
	{
		column = gtk_tree_view_column_new_with_attributes ("Style", gtk_cell_renderer_text_new (), "text", 0, NULL);
		gtk_tree_view_append_column(GTK_TREE_VIEW(m_tvStyles), column);
	}

	GtkTreeIter iter, pHighlightIter;
	bool highlight = false;
	UT_GenericVector<PD_Style*> *pStyles = NULL;
	getDoc()->enumStyles(pStyles);
	for (UT_uint32 i = 0; i < nStyles; i++)
	{
		pStyle = pStyles->getNthItem(i);


		if (!pStyle)
			continue;

		org_name = pStyle->getName();

		std::string sLoc;
		pt_PieceTable::s_getLocalisedStyleName(org_name, sLoc);
		loc_name = sLoc.c_str();

		if ((m_whichType == ALL_STYLES) ||
			(m_whichType == USED_STYLES && pStyle->isUsed()) ||
			(m_whichType == USER_STYLES && pStyle->isUserDefined()) ||
			(!strcmp(m_sNewStyleName.utf8_str(), loc_name)))
		{
			gtk_list_store_append(m_listStyles, &iter);
			gtk_list_store_set(m_listStyles, &iter, 0, loc_name, 1, org_name, -1);

			if (!strcmp(m_sNewStyleName.utf8_str(), loc_name)) {
				pHighlightIter = iter;
				highlight = true;
			}
		}
	}
	DELETEP(pStyles);

	GtkTreeSelection *selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(m_tvStyles));
	if (highlight) {

		GtkTreeModel *sort = gtk_tree_view_get_model(GTK_TREE_VIEW(m_tvStyles));
		gtk_tree_model_sort_convert_child_iter_to_iter(GTK_TREE_MODEL_SORT(sort), &iter, &pHighlightIter);
		gtk_tree_selection_select_iter(selection, &iter);
		GtkTreePath *path = gtk_tree_model_get_path(sort, &iter);
		gtk_tree_view_scroll_to_cell(GTK_TREE_VIEW(m_tvStyles), path, NULL, FALSE, 0, 0);
		gtk_tree_path_free(path);
	}
	else {

		GtkTreePath *path = gtk_tree_path_new_from_string("0");
		gtk_tree_selection_select_path(selection, path);
		gtk_tree_path_free(path);
	}


	s_tvStyles_selection_changed (selection, (gpointer)(this));
}
