playlist_get_blank (void)
{
    int list = playlist_get_active ();
    char * title = playlist_get_title (list);

    if (strcmp (title, _(default_title)) || playlist_entry_count (list) > 0)
    {
        list = playlist_count ();
        playlist_insert (list);
    }

    str_unref (title);
    return list;
}
