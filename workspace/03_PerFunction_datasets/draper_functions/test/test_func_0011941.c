report_config_mixed_list_add_div ( gboolean is_categ,
					       const gchar *name,
					       gint number )
{
    GtkTreeModel *model;

    if (is_categ)
	model = model_categ;
    else
	model = model_budget;
    gtk_tree_store_append ( GTK_TREE_STORE (model),
			    &parent_iter,
			    NULL );
    gtk_tree_store_set (GTK_TREE_STORE (model),
			&parent_iter,
			REPORT_CATEG_BUDGET_LIST_NAME, name,
			REPORT_CATEG_BUDGET_LIST_NUMBER, number,
			REPORT_CATEG_BUDGET_LIST_SUB_NUMBER, -1,
			REPORT_CATEG_BUDGET_LIST_ACTIVATABLE, TRUE,
			-1 );
}
