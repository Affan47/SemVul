csv_import_create_model ( GtkTreeView * tree_preview, gchar * contents,
                        gchar * separator )
{
    GtkWidget * assistant;
    GtkTreeStore *model;
    GtkTreeViewColumn * col;
    GtkCellRenderer * cell;
    GType *types;
    gint size, i;
    GList *list;

    size = csv_import_count_columns ( contents, separator );
    if ( ! size || ! contents)
	    return NULL;

    csv_fields_config = csv_import_update_fields_config ( contents, size, separator );

    assistant = g_object_get_data ( G_OBJECT(tree_preview), "assistant" );


    list = gtk_tree_view_get_columns ( GTK_TREE_VIEW ( tree_preview ) );

    while ( list )
    {
        gtk_tree_view_remove_column ( tree_preview, list -> data );
        list = list -> next;
    }

    types = (GType *) g_malloc0 ( ( size + 2 ) * sizeof ( GType * ) );

    types[0] = G_TYPE_BOOLEAN;
    cell = gtk_cell_renderer_toggle_new ();
    col = gtk_tree_view_column_new_with_attributes ( _("Skip"),
					    cell,
                        "active", 0,
					    NULL);
    gtk_tree_view_append_column ( tree_preview, col );
    g_object_set_data ( G_OBJECT ( col ), "assistant", assistant );
    g_signal_connect ( cell,
                        "toggled",
                        G_CALLBACK ( skip_line_toggled ),
                        tree_preview );

    for ( i = 0 ; i < size ; i ++ )
    {
        GtkWidget *label;
        gchar *name;

        types[i+1] = G_TYPE_STRING;

        cell = gtk_cell_renderer_text_new ();
        col = gtk_tree_view_column_new_with_attributes (
                        NULL,
                        cell,
                        "text", i + 1,
                        "strikethrough", 0,
                        NULL);

        if ( csv_fields_config[i] > 0 )
        {
            name = g_strconcat ( "<b><u>", _( csv_fields [ csv_fields_config[i] ] . name ),
                     "</u></b>", NULL );
        }
        else
        {
            name = my_strdup (_( csv_fields [ csv_fields_config[i] ] . name ));
        }

        label = gtk_label_new ( NULL );
        gtk_label_set_markup ( GTK_LABEL(label), name );
        gtk_widget_show ( label );
        g_free ( name );

        gtk_tree_view_column_set_widget ( col, label );
        gtk_tree_view_append_column ( tree_preview, col );
        gtk_tree_view_column_set_clickable ( col, TRUE );
        g_object_set_data ( G_OBJECT ( col ), "column", col );
        g_object_set_data ( G_OBJECT ( col ), "assistant", assistant );
        g_signal_connect ( G_OBJECT ( col ),
                   "clicked",
                   G_CALLBACK ( csv_import_header_on_click ),
                   GINT_TO_POINTER ( i + 1 ) );
    }

    model =  gtk_tree_store_newv ( size + 1, types );

    return (GtkTreeModel *) model;
}
