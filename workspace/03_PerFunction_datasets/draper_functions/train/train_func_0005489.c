import_selected_files ( GtkWidget *assistant )
{
    GSList *list = NULL;
    GtkTreeModel *model;
    GtkTreeIter iter;

    model = g_object_get_data ( G_OBJECT ( assistant ), "model" );
    g_return_val_if_fail ( model, NULL );

    gtk_tree_model_get_iter_first ( model, &iter );

    do
    {
        struct imported_file *imported;
        gboolean selected;

        imported = g_malloc0 ( sizeof ( struct imported_file ) );
        gtk_tree_model_get ( GTK_TREE_MODEL ( model ), &iter,
                        IMPORT_FILESEL_SELECTED, &selected,
                        IMPORT_FILESEL_REALNAME, &(imported -> name),
                        IMPORT_FILESEL_TYPE, &(imported -> type),
                        IMPORT_FILESEL_CODING, &(imported -> coding_system),
                        -1 );

        if ( selected )
        {
            list = g_slist_append ( list, imported );
        }
    }
    while ( gtk_tree_model_iter_next ( model, &iter ) );

    return list;
}
