lookup_entry (Playlist * playlist, int entry_num)
{
    return (entry_num >= 0 && entry_num < index_count (playlist->entries)) ?
     index_get (playlist->entries, entry_num) : NULL;
}
