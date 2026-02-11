Index_Strand_destroy(Index_Strand *index_strand){
    g_assert(index_strand);
    g_free(index_strand->word_table);
    g_free(index_strand->word_list);
    if(index_strand->index_cache)
        BitArray_destroy(index_strand->index_cache);
    g_free(index_strand);
    return;
    }
