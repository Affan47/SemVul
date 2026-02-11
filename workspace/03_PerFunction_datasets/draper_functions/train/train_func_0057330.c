playlist_get_playing (void)
{
    ENTER;
    int list = playing_playlist ? playing_playlist->number: -1;
    RETURN (list);
}
