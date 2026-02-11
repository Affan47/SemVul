update_homepage_title (GtkEntry *entry, gchar *value,
                        gint length, gint * position)
{
    if ( titre_fichier && strlen ( titre_fichier ) )
        g_free ( titre_fichier );

    titre_fichier = my_strdup ( gtk_entry_get_text ( GTK_ENTRY ( entry ) ) );


    gsb_main_set_grisbi_title ( -1 );


    if ( etat.modification_fichier == 0 )
        modification_fichier ( TRUE );

    return FALSE;
}
