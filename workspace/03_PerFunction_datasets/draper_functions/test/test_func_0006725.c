playlist_trigger_scan (void)
{
    ENTER;

    for (int i = 0; i < index_count (playlists); i ++)
    {
        Playlist * p = index_get (playlists, i);
        p->scanning = TRUE;
    }

    scan_restart ();

    LEAVE;
}
