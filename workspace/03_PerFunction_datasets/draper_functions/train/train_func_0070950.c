gsb_account_create_menu_list ( GtkSignalFunc func,
					  gboolean activate_currrent,
					  gboolean include_closed )
{
    GtkWidget *menu;
    GtkWidget *item;
    GSList *list_tmp;

    menu = gtk_menu_new ();

    list_tmp = gsb_data_account_get_list_accounts ();

    while ( list_tmp )
    {
	gint i;

	i = gsb_data_account_get_no_account ( list_tmp -> data );

	if (  i >= 0 && ( !gsb_data_account_get_closed_account (i) || include_closed ) )
	{
	    item = gtk_menu_item_new_with_label ( gsb_data_account_get_name (i));
	    g_object_set_data ( G_OBJECT ( item ),
				  "account_number",
				  GINT_TO_POINTER (i));
	    if ( func )
		g_signal_connect ( G_OBJECT ( item ), "activate", G_CALLBACK(func), NULL );
	    gtk_menu_shell_append ( GTK_MENU_SHELL ( menu ), item );

	    if ( !activate_currrent &&
		 gsb_gui_navigation_get_current_account () == i)
	    {
		gtk_widget_set_sensitive ( item, FALSE );
	    }

	    gtk_widget_show ( item );
	}
	list_tmp = list_tmp -> next;
    }

    return ( menu );
}
