playlist_insert_with_id (int at, int id)
{
    ENTER;

    if (at < 0 || at > index_count (playlists))
        at = index_count (playlists);

    index_insert (playlists, at, playlist_new (id));
    number_playlists (at, index_count (playlists) - at);

    queue_update (PLAYLIST_UPDATE_STRUCTURE, -1, 0, 0);
    LEAVE;
}
