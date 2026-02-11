list_get_value (void * user, int row, int column, GValue * value)
{
    g_return_if_fail (search_matches);
    g_return_if_fail (column >= 0 && column < 2);
    g_return_if_fail (row >= 0 && row < search_matches->len);

    int playlist = aud_playlist_get_active ();
    int entry = g_array_index (search_matches, int, row);

    switch (column)
    {
    case 0:
        g_value_set_int (value, 1 + entry);
        break;
    case 1:;
        char * title = aud_playlist_entry_get_title (playlist, entry, TRUE);
        g_return_if_fail (title);
        g_value_set_string (value, title);
        str_unref (title);
        break;
    }
}
