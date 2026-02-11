ario_search_do_search (ArioSearch *search)
{
        ARIO_LOG_FUNCTION_START;
        ArioServerAtomicCriteria *atomic_criteria;
        GSList *criteria = NULL;
        GSList *tmp;
        GSList *songs;
        ArioServerSong *song;
        GtkTreeIter iter;
        gchar *title;
        GtkListStore *liststore;
        int i;
        gchar **cmp_str;


        cmp_str = g_strsplit (gtk_entry_get_text (GTK_ENTRY (search->priv->entry)), " ", -1);
        if (!cmp_str)
                return FALSE;


        for (i = 0; cmp_str[i]; ++i) {

                if (g_utf8_collate (cmp_str[i], "")
                    && strlen(cmp_str[i]) > 2)
                {
                        atomic_criteria = (ArioServerAtomicCriteria *) g_malloc (sizeof (ArioServerAtomicCriteria));
                        atomic_criteria->tag = ARIO_TAG_ANY;
                        atomic_criteria->value = g_strdup(cmp_str[i]);
                        criteria = g_slist_append (criteria, atomic_criteria);
                }
        }
        g_strfreev (cmp_str);


        liststore = ario_songlist_get_liststore (ARIO_SONGLIST (search->priv->searchs));
        gtk_list_store_clear (liststore);

        if (!criteria)
                return FALSE;


        songs = ario_server_get_songs (criteria, FALSE);

        g_slist_foreach (criteria, (GFunc) g_free, NULL);
        g_slist_free (criteria);


        for (tmp = songs; tmp; tmp = g_slist_next (tmp)) {
                song = tmp->data;


                gtk_list_store_append (liststore, &iter);
                title = ario_util_format_title (song);
                gtk_list_store_set (liststore, &iter,
                                    SONGS_TITLE_COLUMN, title,
                                    SONGS_ARTIST_COLUMN, song->artist,
                                    SONGS_ALBUM_COLUMN, song->album,
                                    SONGS_FILENAME_COLUMN, song->file,
                                    -1);
        }
        g_slist_foreach (songs, (GFunc) ario_server_free_song, NULL);
        g_slist_free (songs);

        return FALSE;
}
