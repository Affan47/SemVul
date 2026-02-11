check_iter (TotemPlPlaylist     *playlist,
            TotemPlPlaylistIter *iter)
{
        TotemPlPlaylistPrivate *priv;

        if (!iter) {
                return FALSE;
        }

        if (iter->data1 != playlist) {
                return FALSE;
        }

        priv = TOTEM_PL_PLAYLIST_GET_PRIVATE (playlist);

        if (g_list_position (priv->items, iter->data2) == -1) {
                return FALSE;
        }

        return TRUE;
}
