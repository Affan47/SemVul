data_end_element (GMarkupParseContext *context,
                       const gchar         *element_name,
                       gpointer             user_data,
                       GError             **error) {
    gchar * latin1_path;
    song_parse_state * state = (song_parse_state *) user_data;
    if (get_element((char *) element_name) == E_FILE) {
        if (state->new && state->s) {

            latin1_path = strdup_to_latin1(state->s->path);
            state->s->access_ok = !access(latin1_path, R_OK);
            if (!state->s->access_ok) {
                gjay->songs_dirty = TRUE;
            }
            g_free(latin1_path);


            gjay->songs = g_list_append(gjay->songs, state->s);
            g_hash_table_insert (gjay->song_name_hash,
                                 state->s->path,
                                 state->s);
            hash_inode_dev(state->s, state->has_dev);
            g_hash_table_insert (gjay->song_inode_dev_hash,
                                 &state->s->inode_dev_hash,
                                 state->s);
        }


        if (!(state->not_song || state->is_repeat))
            song_set_repeat_attrs(state->s);
    }
    state->element = E_LAST;
}
