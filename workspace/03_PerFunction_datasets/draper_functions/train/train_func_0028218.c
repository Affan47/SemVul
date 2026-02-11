get_value (void * user, int row, int column, GValue * value)
{
    int list = aud_playlist_get_active ();
    int entry = aud_playlist_queue_get_entry (list, row);

    switch (column)
    {
    case COLUMN_ENTRY:
        g_value_set_int (value, 1 + entry);
        break;
    case COLUMN_TITLE:;
        char * title = aud_playlist_entry_get_title (list, entry, TRUE);
        g_value_set_string (value, title);
        str_unref (title);
        break;
    }
}
