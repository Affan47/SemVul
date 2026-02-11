update (void * unused)
{
    ENTER;

    for (int i = 0; i < index_count (playlists); i ++)
    {
        Playlist * p = index_get (playlists, i);
        memcpy (& p->last_update, & p->next_update, sizeof (Update));
        memset (& p->next_update, 0, sizeof (Update));
    }

    int level = update_level;
    update_level = 0;

    if (update_source)
    {
        g_source_remove (update_source);
        update_source = 0;
    }

    LEAVE;

    hook_call ("playlist update", GINT_TO_POINTER (level));
    return FALSE;
}
