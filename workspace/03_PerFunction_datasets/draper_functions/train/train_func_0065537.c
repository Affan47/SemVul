Load_Genres_List_To_UI (void)
{
    gsize i;

    g_return_if_fail (GenreComboModel != NULL);

    gtk_list_store_insert_with_values (GTK_LIST_STORE (GenreComboModel), NULL,
                                       G_MAXINT, MISC_COMBO_TEXT, "", -1);
    gtk_list_store_insert_with_values (GTK_LIST_STORE (GenreComboModel), NULL,
                                       G_MAXINT, MISC_COMBO_TEXT, "Unknown",
                                       -1);

    for (i = 0; i <= GENRE_MAX; i++)
    {
        gtk_list_store_insert_with_values (GTK_LIST_STORE (GenreComboModel),
                                           NULL, G_MAXINT, MISC_COMBO_TEXT,
                                           id3_genres[i], -1);
    }
}
