bet_config_general_get_period_widget ( GtkWidget *container )
{
    GtkWidget *vbox;
    GtkWidget *label;
    GtkWidget *button_1, *button_2;
    GtkWidget *hbox;
    GtkSizeGroup *size_group;
    gchar *text;


    size_group = gtk_size_group_new ( GTK_SIZE_GROUP_HORIZONTAL );

    vbox = gtk_vbox_new ( FALSE, 5 );
    gtk_box_pack_start ( GTK_BOX ( container ), vbox, FALSE, FALSE, 5);

    label = gtk_label_new ( _("Beginning of period") );
    gtk_misc_set_alignment ( GTK_MISC ( label ), 0, 0.5);
    gtk_label_set_justify ( GTK_LABEL ( label ), GTK_JUSTIFY_LEFT );
    gtk_box_pack_start ( GTK_BOX ( vbox ), label, FALSE, FALSE, 5) ;

    hbox = gtk_hbox_new ( FALSE, 5 );
    gtk_box_pack_start ( GTK_BOX ( vbox ), hbox, FALSE, FALSE, 5) ;

    button_1 = gtk_radio_button_new_with_label ( NULL,
                        _("1st day of month") );
    gtk_widget_set_name ( button_1, "bet_period_button_1" );
    gtk_size_group_add_widget ( GTK_SIZE_GROUP ( size_group ), button_1 );

    button_2 = gtk_radio_button_new_with_label_from_widget (
                        GTK_RADIO_BUTTON ( button_1 ),
                        _("date today") );

    if ( etat.bet_deb_period == 1 )
        gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( button_1 ), TRUE );
    else
        gtk_toggle_button_set_active ( GTK_TOGGLE_BUTTON ( button_2 ), TRUE );

    gtk_box_pack_start ( GTK_BOX ( hbox ), button_1, FALSE, FALSE, 5) ;
    gtk_box_pack_start ( GTK_BOX ( hbox ), button_2, FALSE, FALSE, 5) ;


    g_signal_connect (G_OBJECT ( button_1 ),
                        "button-release-event",
                        G_CALLBACK ( bet_config_period_clicked ),
                        NULL );
    g_signal_connect (G_OBJECT ( button_2 ),
                        "button-release-event",
                        G_CALLBACK ( bet_config_period_clicked ),
                        NULL );

    text = make_blue ( _("Note: This option is used if no starting date for forecasts.") );
    label = gtk_label_new ( text );
    gtk_label_set_use_markup ( GTK_LABEL(label), TRUE );
    gtk_misc_set_alignment ( GTK_MISC ( label ), 0, 0.5);
    gtk_label_set_justify ( GTK_LABEL ( label ), GTK_JUSTIFY_LEFT );
    gtk_box_pack_start ( GTK_BOX ( vbox ), label, FALSE, FALSE, 5) ;
    g_free ( text );

    gtk_widget_show_all ( vbox );

    return vbox;
}
