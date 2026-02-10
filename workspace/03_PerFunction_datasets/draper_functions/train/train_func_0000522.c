custom_list_iter_nth_child (GtkTreeModel *tree_model,
					    GtkTreeIter  *iter,
					    GtkTreeIter  *parent,
					    gint          n)
{
    CustomList    *custom_list;
    CustomRecord  *parent_record;

    g_return_val_if_fail (CUSTOM_IS_LIST (tree_model), FALSE);
    g_return_val_if_fail (iter != NULL, FALSE);

    custom_list = CUSTOM_LIST(tree_model);

    if (parent == NULL)
    {

	if( n >= custom_list->num_visibles_rows )
	    return FALSE;

	iter->stamp = custom_list->stamp;
	iter->user_data = custom_list->visibles_rows[n];
	return TRUE;
    }


    parent_record = parent->user_data;
    g_return_val_if_fail (parent_record != NULL, FALSE);


    if (n >= parent_record -> number_of_children
	||
	!parent_record -> has_expander)
	return FALSE;


    iter->stamp     = custom_list->stamp;
    iter->user_data = parent_record -> children_rows[n];
    return TRUE;
}
