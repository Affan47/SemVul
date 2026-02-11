load_prefs ( void ) {
    GMarkupParseContext * parse_context;
    GMarkupParser parser;
    gboolean result = TRUE;
    GError * error;
    char buffer[BUFFER_SIZE];
    FILE * f;
    gssize text_len;
    pref_element_type element;
    GjayPrefs *prefs;


    prefs = g_malloc0(sizeof(GjayPrefs));
    gjay->prefs = prefs;

    prefs->rating = DEFAULT_RATING;
    prefs->use_ratings = FALSE;
    prefs->time = DEFAULT_PLAYLIST_TIME;
    prefs->max_working_set = DEFAULT_MAX_WORKING_SET;
    prefs->variance =
        prefs->hue =
        prefs->brightness =
        prefs->bpm =
        prefs->freq =
        prefs->path_weight = DEFAULT_CRITERIA;
    prefs->saturation = 1;
    prefs->extension_filter = TRUE;
    prefs->color.H = 0;
    prefs->color.S = 0.5;
    prefs->color.V = 1.0;
    prefs->use_hsv = FALSE;
    prefs->daemon_action = PREF_DAEMON_QUIT;
    prefs->hide_tips = FALSE;
    snprintf(buffer, BUFFER_SIZE, "%s/%s/%s", getenv("HOME"),
             GJAY_DIR, GJAY_PREFS);
    prefs->music_player = 0;
    prefs->music_player_name = g_strdup(music_player_names[0]);

    f = fopen(buffer, "r");
    if (f) {
        parser.start_element = data_start_element;
        parser.text = data_text;
        parser.end_element = NULL;

        parse_context = g_markup_parse_context_new(&parser, 0, &element, NULL);
        while (result && !feof(f)) {
            text_len = fread(buffer, 1, BUFFER_SIZE, f);
            result = g_markup_parse_context_parse ( parse_context,
                                                    buffer,
                                                    text_len,
                                                    &error);
            error = NULL;
        }
        g_markup_parse_context_free(parse_context);
        fclose(f);
    }
    return prefs;
}
