bet_finance_data_list_context_menu ( GtkWidget *tree_view, gint page_num )
{
    GtkWidget *menu, *menu_item;
    GtkWidget *image;
    GtkTreeModel *model;
    GtkTreeSelection *tree_selection;
    GtkTreeIter iter;
    gchar *tmp_str;
    gint origin;

    tree_selection = gtk_tree_view_get_selection ( GTK_TREE_VIEW ( tree_view ) );

    if ( !gtk_tree_selection_get_selected ( GTK_TREE_SELECTION ( tree_selection ),
     &model, &iter ) )
        return;

    menu = gtk_menu_new ();

    origin = GPOINTER_TO_INT ( g_object_get_data ( G_OBJECT ( tree_view ), "origin" ) );

    tmp_str = g_build_filename ( GRISBI_PIXMAPS_DIR, "ac_liability_16.png", NULL);
    image = gtk_image_new_from_file ( tmp_str );
    gtk_image_set_pixel_size ( GTK_IMAGE ( image ), GTK_ICON_SIZE_MENU );
    g_free ( tmp_str );

    if ( origin == SPP_ORIGIN_SIMULATOR )
    {
        if ( page_num == 0 )
        {
            menu_item = gtk_image_menu_item_new_with_label ( _("View amortization table") );
            g_signal_connect ( G_OBJECT ( menu_item ),
                        "activate",
                        G_CALLBACK ( bet_finance_fill_amortization_array ),
                        tree_selection );
        }
        else
        {
            menu_item = gtk_image_menu_item_new_with_label ( _("View credits simulator") );
            g_signal_connect ( G_OBJECT ( menu_item ),
                        "activate",
                        G_CALLBACK ( bet_finance_switch_simulator_page ),
                        NULL );
        }

    }
    else
    {
        gboolean amortization_initial_date;

        amortization_initial_date = GPOINTER_TO_INT ( g_object_get_data (
                        G_OBJECT ( tree_view ), "amortization_initial_date" ) );

        if ( amortization_initial_date )
            menu_item = gtk_image_menu_item_new_with_label ( _("Show amortization schedule to date") );
        else
            menu_item = gtk_image_menu_item_new_with_label ( _("Show amortization schedule from the beginning") );

        g_signal_connect ( G_OBJECT ( menu_item ),
                        "activate",
                        G_CALLBACK ( bet_finance_switch_amortization_initial_date ),
                        tree_view );
    }

    gtk_image_menu_item_set_image ( GTK_IMAGE_MENU_ITEM ( menu_item ), image );
    gtk_menu_shell_append ( GTK_MENU_SHELL ( menu ), menu_item );


    gtk_menu_shell_append ( GTK_MENU_SHELL ( menu ), gtk_separator_menu_item_new() );


    menu_item = gtk_image_menu_item_new_with_label ( _("Print the array") );
    gtk_image_menu_item_set_image ( GTK_IMAGE_MENU_ITEM ( menu_item ),
                        gtk_image_new_from_stock ( GTK_STOCK_PRINT, GTK_ICON_SIZE_MENU ) );
    g_signal_connect ( G_OBJECT ( menu_item ),
                        "activate",
                        G_CALLBACK ( print_tree_view_list ),
                        tree_view );
    gtk_menu_shell_append ( GTK_MENU_SHELL ( menu ), menu_item );


    menu_item = gtk_image_menu_item_new_with_label ( _("Export the array") );
    gtk_image_menu_item_set_image ( GTK_IMAGE_MENU_ITEM ( menu_item ),
                        gtk_image_new_from_stock ( GTK_STOCK_SAVE, GTK_ICON_SIZE_MENU ) );
    g_signal_connect ( G_OBJECT ( menu_item ),
                        "activate",
                        G_CALLBACK ( bet_finance_ui_export_tab ),
                        tree_view );
    gtk_menu_shell_append ( GTK_MENU_SHELL ( menu ), menu_item );


    gtk_widget_show_all ( menu );
    gtk_menu_popup ( GTK_MENU( menu ), NULL, NULL, NULL, NULL, 3,
                        gtk_get_current_event_time ( ) );
}
