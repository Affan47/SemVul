set_position (Playlist * playlist, Entry * entry, bool_t update_shuffle)
{
    playlist->position = entry;
    playlist->resume_time = 0;


    if (entry && update_shuffle)
        entry->shuffle_num = ++ playlist->last_shuffle_num;
}
