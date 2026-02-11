shuffle_prev (Playlist * playlist)
{
    int entries = index_count (playlist->entries);
    Entry * found = NULL;

    for (int count = 0; count < entries; count ++)
    {
        Entry * entry = index_get (playlist->entries, count);

        if (entry->shuffle_num && (! playlist->position ||
         entry->shuffle_num < playlist->position->shuffle_num) && (! found
         || entry->shuffle_num > found->shuffle_num))
            found = entry;
    }

    if (! found)
        return FALSE;

    set_position (playlist, found, FALSE);
    return TRUE;
}
