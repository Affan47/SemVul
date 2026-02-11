ui_jump_to_track_cache_search (JumpToTrackCache * cache, const
 char * keyword)
{
    char * normalized_keyword = g_utf8_casefold (keyword, -1);
    GString* keyword_string = g_string_new(normalized_keyword);
    GString* match_string = g_string_new(normalized_keyword);
    int match_string_length = keyword_string->len;

    while (match_string_length >= 0)
    {
        gpointer string_ptr =  GINT_TO_POINTER(g_string_hash(match_string));
        gpointer result_entries = g_hash_table_lookup(cache->keywords,
                                                      string_ptr);
        if (result_entries != NULL)
        {
            KeywordMatches* matched_entries = (KeywordMatches*)result_entries;


            if (match_string_length == keyword_string->len) {
                g_string_free(keyword_string, TRUE);
                g_string_free(match_string, TRUE);
                g_free(normalized_keyword);
                return matched_entries->entries;
            }


            GArray* result = ui_jump_to_track_cache_match_keyword(cache,
                                                                  matched_entries,
                                                                  keyword_string);
            g_string_free(keyword_string, TRUE);
            g_string_free(match_string, TRUE);
            g_free(normalized_keyword);
            return result;
        }
        match_string_length--;
        g_string_set_size(match_string, match_string_length);
    }


    AUDDBG("One should never get to this point. Something is really wrong with \
cache->keywords hash table.");
    abort ();
}
