info_tree_compare_val_func(GtkTreeModel * model,
			   GtkTreeIter * a,
			   GtkTreeIter * b, gpointer userdata)
{
    gint ret = 0;
    gchar *col1, *col2;

    gtk_tree_model_get(model, a, INFO_TREE_COL_VALUE, &col1, -1);
    gtk_tree_model_get(model, b, INFO_TREE_COL_VALUE, &col2, -1);

    if (col1 == NULL || col2 == NULL) {
	if (col1 == NULL && col2 == NULL)
	    return 0;

	ret = (col1 == NULL) ? -1 : 1;
    } else {
	ret = shell->_order_type ? (atof(col1) < atof(col2)) :
	    (atof(col1) > atof(col2));
    }

    g_free(col1);
    g_free(col2);

    return ret;
}
