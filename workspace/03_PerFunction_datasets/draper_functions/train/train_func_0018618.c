ui_jump_to_track_cache_regex_list_create(const GString* keyword)
{
    GSList *regex_list = NULL;
    char **words = NULL;
    int i = -1;

    words = g_strsplit(keyword->str, " ", 0);


    while ( words[++i] != NULL )
    {

        if (words[i][0] == 0) {
            continue;
        }
        regex_t *regex = g_malloc(sizeof(regex_t));
    #if defined(USE_REGEX_PCRE)
        if ( regcomp( regex , words[i] , REG_NOSUB | REG_UTF8 ) == 0 )
    #else
        if ( regcomp( regex , words[i] , REG_NOSUB ) == 0 )
    #endif
            regex_list = g_slist_append( regex_list , regex );
        else
            g_free( regex );
    }

    g_strfreev(words);

    return regex_list;
}
