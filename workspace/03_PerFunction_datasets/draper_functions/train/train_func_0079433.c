entries_are_scanned (Playlist * playlist, bool_t selected)
{
    int entries = index_count (playlist->entries);
    for (int count = 0; count < entries; count ++)
    {
        Entry * entry = index_get (playlist->entries, count);
        if (selected && ! entry->selected)
            continue;

        if (! entry->tuple)
        {
            interface_show_error (_("The playlist cannot be sorted because "
             "metadata scanning is still in progress (or has been disabled)."));
            return FALSE;
        }
    }

    return TRUE;
}
