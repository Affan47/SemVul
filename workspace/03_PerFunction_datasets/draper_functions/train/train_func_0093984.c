Cddb_Album_List_Set_Row_Appearance (GtkTreeIter *row)
{
    CddbAlbum *cddbalbum = NULL;

    gtk_tree_model_get(GTK_TREE_MODEL(CddbAlbumListModel), row,
                       CDDB_ALBUM_LIST_DATA, &cddbalbum, -1);

    if (cddbalbum->track_list != NULL)
    {
        if (CHANGED_FILES_DISPLAYED_TO_BOLD)
        {
            gtk_list_store_set(CddbAlbumListModel, row,
                               CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_NORMAL,
                               CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_BOLD,
                               CDDB_ALBUM_LIST_FOREGROUND_COLOR, NULL,-1);
        } else
        {
            if (cddbalbum->other_version == TRUE)
            {
                gtk_list_store_set(CddbAlbumListModel, row,
                                   CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_NORMAL,
                                   CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_NORMAL,
                                   CDDB_ALBUM_LIST_FOREGROUND_COLOR, &LIGHT_RED, -1);
            } else
            {
                gtk_list_store_set(CddbAlbumListModel, row,
                                   CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_NORMAL,
                                   CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_NORMAL,
                                   CDDB_ALBUM_LIST_FOREGROUND_COLOR, &RED, -1);
            }
        }
    } else
    {
        if (cddbalbum->other_version == TRUE)
        {
            if (CHANGED_FILES_DISPLAYED_TO_BOLD)
            {
                gtk_list_store_set(CddbAlbumListModel, row,
                                   CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_ITALIC,
                                   CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_NORMAL,
                                   CDDB_ALBUM_LIST_FOREGROUND_COLOR, NULL,-1);
            } else
            {
                gtk_list_store_set(CddbAlbumListModel, row,
                                   CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_NORMAL,
                                   CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_NORMAL,
                                   CDDB_ALBUM_LIST_FOREGROUND_COLOR, &GREY, -1);
            }
        } else
        {
            gtk_list_store_set(CddbAlbumListModel, row,
                               CDDB_ALBUM_LIST_FONT_STYLE,       PANGO_STYLE_NORMAL,
                               CDDB_ALBUM_LIST_FONT_WEIGHT,      PANGO_WEIGHT_NORMAL,
                               CDDB_ALBUM_LIST_FOREGROUND_COLOR, NULL, -1);
        }
    }
}
