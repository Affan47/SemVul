ario_browser_goto_playling_song (ArioSource *source)
{
        ARIO_LOG_FUNCTION_START;
        ArioBrowser *browser = ARIO_BROWSER (source);
        GSList *tmp;
        ArioServerSong *song = ario_server_get_current_song ();


        if (!song)
                return;


        for (tmp = browser->priv->trees; tmp; tmp = g_slist_next (tmp)) {
                ario_tree_goto_playling_song (ARIO_TREE (tmp->data), song);
        }
}
