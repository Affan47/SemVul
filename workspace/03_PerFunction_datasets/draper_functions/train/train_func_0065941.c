data_text ( GMarkupParseContext *context,
                 const gchar         *text,
                 gsize                text_len,
                 gpointer             user_data,
                 GError             **error) {
    song_parse_state * state = (song_parse_state *) user_data;
    gchar buffer[BUFFER_SIZE];
    gchar * buffer_str;
    int n;

    memset(buffer, 0x00, BUFFER_SIZE);
    memcpy(buffer, text, text_len);

    switch(state->element) {
    case E_TITLE:
        if (state->new) {
            g_free(state->s->title);
            state->s->title = g_strdup(buffer);
        }
        break;
    case E_ARTIST:
        if (state->new) {
            g_free(state->s->artist);
            state->s->artist = g_strdup(buffer);
        }
        break;
    case E_ALBUM:
        if (state->new) {
            g_free(state->s->album);
            state->s->album = g_strdup(buffer);
        }
        break;
    case E_INODE:
        state->s->inode = atol(buffer);
        break;
    case E_DEV:
        state->s->dev = atol(buffer);
        state->has_dev = TRUE;
        break;
    case E_LENGTH:
        state->s->length = atoi(buffer);
        break;
    case E_RATING:
        state->s->rating = strtof_gjay(buffer, NULL);
        break;
    case E_BPM:
        if (strcmp(buffer, "undef") == 0) {
            state->s->bpm_undef = TRUE;
        } else {
            state->s->bpm = strtof_gjay(buffer, NULL);
        }
        break;
    case E_COLOR:
        if (state->use_hb) {
            HB hb;
            hb.H = strtof_gjay(buffer, &buffer_str);
            hb.B = strtof_gjay(buffer_str, NULL);
            state->s->color = hb_to_hsv(hb);
        } else {
            state->s->color.H = strtof_gjay(buffer, &buffer_str);
            state->s->color.S = strtof_gjay(buffer_str, &buffer_str);
            state->s->color.V = strtof_gjay(buffer_str, NULL);
        }
        break;
    case E_FREQ:
        buffer_str = buffer;
        for (n = 0; n < NUM_FREQ_SAMPLES; n++) {
            state->s->freq[n] = strtof_gjay(buffer_str, &buffer_str);
        }
        break;
    default:
        break;
    }
}
