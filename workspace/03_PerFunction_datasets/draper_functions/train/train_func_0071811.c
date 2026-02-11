getIterLast( GtkTreeView* tv )
{
    GtkTreeModel* model = gtk_tree_view_get_model( tv );
    GtkTreeIter ret;
    int valid = gtk_tree_model_get_iter_first( model, &ret );
    UT_DEBUGMSG((" getIterLast() start...\n"));
    for( GtkTreeIter iter = ret; valid; )
    {
        UT_DEBUGMSG((" getIterLast() loop...\n"));
        valid = gtk_tree_model_iter_next ( model, &iter );
        if( valid )
            ret = iter;
    }
    return ret;
}
