Cddb_Load_Album_List (gboolean only_red_lines)
{
    if (CddbWindow && CddbAlbumList && CddbAlbumListView)
    {
        GtkTreeIter iter;
        GList *l;

        GtkTreeSelection *selection;
        GList            *selectedRows = NULL;
        GtkTreeIter       currentIter;
        CddbAlbum        *cddbalbumSelected = NULL;


        selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(CddbAlbumListView));
        selectedRows = gtk_tree_selection_get_selected_rows(selection, NULL);
        if (selectedRows)
        {
            if (gtk_tree_model_get_iter(GTK_TREE_MODEL(CddbAlbumListModel), &currentIter, (GtkTreePath*)selectedRows->data))
                gtk_tree_model_get(GTK_TREE_MODEL(CddbAlbumListModel), &currentIter,
                                   CDDB_ALBUM_LIST_DATA, &cddbalbumSelected, -1);
        }


        gtk_list_store_clear(CddbAlbumListModel);


        for (l = g_list_first (CddbAlbumList); l != NULL; l = g_list_next (l))
        {
            CddbAlbum *cddbalbum = l->data;

            if ( (only_red_lines && cddbalbum->track_list) || !only_red_lines)
            {

                gtk_list_store_insert_with_values (CddbAlbumListModel, &iter,
                                                   G_MAXINT,
                                                   CDDB_ALBUM_LIST_PIXBUF,
                                                   cddbalbum->bitmap,
                                                   CDDB_ALBUM_LIST_ALBUM,
                                                   cddbalbum->artist_album,
                                                   CDDB_ALBUM_LIST_CATEGORY,
                                                   cddbalbum->category,
                                                   CDDB_ALBUM_LIST_DATA,
                                                   cddbalbum, -1);

                Cddb_Album_List_Set_Row_Appearance(&iter);


                if (cddbalbum == cddbalbumSelected)
                    gtk_tree_selection_select_iter(gtk_tree_view_get_selection(GTK_TREE_VIEW(CddbAlbumListView)), &iter);
            }
        }
    }
}
