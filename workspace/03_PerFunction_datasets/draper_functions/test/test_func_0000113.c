metatree_get ( GtkTreeModel * model, GtkTreePath * path,
                        gint column, gint *data )
{
    GtkTreeIter iter;

    if ( gtk_tree_model_get_iter ( model, &iter, path ) && data )
    {
	gtk_tree_model_get ( model, &iter, column, data, -1 );
	return TRUE;
    }
    return FALSE;
}
