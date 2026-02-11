select_all (void * user, bool_t selected)
{
    int list = aud_playlist_get_active ();
    int count = aud_playlist_queue_count (list);

    for (int i = 0; i < count; i ++)
        aud_playlist_entry_set_selected (list, aud_playlist_queue_get_entry (list, i), selected);
}
