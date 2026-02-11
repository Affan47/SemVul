update_progress()
{
    GtkTreeModel *model = shell->info->model;
    GtkTreeStore *store = GTK_TREE_STORE(model);
    GtkTreeIter iter, fiter;
    gchar *tmp;
    gdouble maxv = 0, maxp = 0, cur, floatval;

    gtk_tree_model_get_iter_first(model, &fiter);


    if (shell->normalize_percentage) {
	iter = fiter;
	do {
		gtk_tree_model_get(model, &iter, INFO_TREE_COL_VALUE, &tmp, -1);

		cur = atof(tmp);
		maxv = MAX(maxv, cur);

		g_free(tmp);
	} while (gtk_tree_model_iter_next(model, &iter));
    } else {
	maxv = 100.0f;
    }


    if (shell->_order_type == SHELL_ORDER_ASCENDING) {
	iter = fiter;
	do {
	    gtk_tree_model_get(model, &iter, INFO_TREE_COL_VALUE, &tmp, -1);

	    cur = 100 - 100 * atof(tmp) / maxv;
	    maxp = MAX(cur, maxp);

	    g_free(tmp);
	} while (gtk_tree_model_iter_next(model, &iter));

	maxp = 100 - maxp;
    }


    iter = fiter;
    do {
        char *strval;

	gtk_tree_model_get(model, &iter, INFO_TREE_COL_VALUE, &tmp, -1);
	floatval = atof(tmp);
	strval = g_strdup(tmp);
	g_free(tmp);

	cur = 100 * floatval / maxv;

	if (shell->_order_type == SHELL_ORDER_ASCENDING)
	    cur = 100 - cur + maxp;

        if (strchr(strval, ' ')) {
            tmp = g_strdup_printf("%.2f%s", floatval, strchr(strval, ' '));
        } else {
            tmp = g_strdup_printf("%.2f", floatval);
        }

        tmp = strreplace(tmp, ",", '.');
	gtk_tree_store_set(store, &iter, INFO_TREE_COL_PROGRESS, cur,
                                         INFO_TREE_COL_VALUE, tmp, -1);
        g_free(tmp);
        g_free(strval);
    } while (gtk_tree_model_iter_next(model, &iter));


    GtkTreeSortable *sortable = GTK_TREE_SORTABLE(shell->info->model);

    gtk_tree_sortable_set_sort_func(sortable, INFO_TREE_COL_VALUE,
				    info_tree_compare_val_func, 0, NULL);
    gtk_tree_sortable_set_sort_column_id(sortable,
					 INFO_TREE_COL_VALUE,
					 GTK_SORT_DESCENDING);
    gtk_tree_view_set_model(GTK_TREE_VIEW(shell->info->view),
			    GTK_TREE_MODEL(sortable));
}
