change_logo_accueil ( GtkWidget * file_selector )
{
    GdkPixbuf * pixbuf;

    const gchar *selected_filename;

    selected_filename = file_selection_get_filename ( GTK_FILE_CHOOSER ( file_selector ) );

    if ( gsb_data_account_get_accounts_amount () )
    {

        gchar * chemin_logo;

        gtk_container_remove ( GTK_CONTAINER ( logo_button ), preview );
        chemin_logo = g_strstrip ( g_strdup ( selected_filename ) );
        if ( !strlen ( chemin_logo ) )
        {
            if ( logo_accueil && GTK_IS_WIDGET ( logo_accueil ) )
                gtk_widget_hide ( logo_accueil );
            preview = gtk_image_new_from_stock ( GTK_STOCK_MISSING_IMAGE,
                             GTK_ICON_SIZE_BUTTON );
        }
        else
        {

            pixbuf = gdk_pixbuf_new_from_file ( chemin_logo, NULL );
            if (!pixbuf)
            {
                if ( logo_accueil && GTK_IS_WIDGET ( logo_accueil ))
                    gtk_widget_hide ( logo_accueil );
                preview = gtk_image_new_from_stock ( GTK_STOCK_MISSING_IMAGE,
                                    GTK_ICON_SIZE_BUTTON );
            }
            else
            {
                if ( g_strcmp0 ( g_path_get_dirname ( chemin_logo ), GRISBI_PIXMAPS_DIR ) == 0 )
                {
                    gchar *name_logo;

                    etat.is_pixmaps_dir = TRUE;

                    name_logo = g_path_get_basename ( chemin_logo );
                    if ( g_strcmp0 ( name_logo, "grisbi-logo.png" ) != 0 )
                        etat.name_logo = name_logo;
                    else
                        etat.name_logo = NULL;
                }
                else
                {
                    etat.is_pixmaps_dir = FALSE;
                    if ( etat.name_logo && strlen ( etat.name_logo ) )
                        g_free ( etat.name_logo );
                    etat.name_logo = NULL;
                }

                gsb_select_icon_set_logo_pixbuf ( pixbuf );
                preview = gtk_image_new_from_pixbuf (
                        gdk_pixbuf_scale_simple (
                        pixbuf, 48, 48, GDK_INTERP_BILINEAR ) );


                gtk_widget_destroy ( logo_accueil );

                logo_accueil =  gtk_image_new_from_pixbuf (
                                    gsb_select_icon_get_logo_pixbuf ( ) );
                gtk_box_pack_start ( GTK_BOX ( hbox_title ), logo_accueil, FALSE, FALSE, 0 );
                gtk_widget_show ( logo_accueil );

                gtk_window_set_default_icon (
                            gsb_select_icon_get_logo_pixbuf ( ) );
            }

            g_free ( chemin_logo );
        }
        gtk_widget_show ( preview );
        gtk_container_add ( GTK_CONTAINER ( logo_button ), preview );


        if ( etat.modification_fichier == 0 )
            modification_fichier ( TRUE );
    }
}
