text_allocate_arrays(void)
{   abbreviations_at = my_malloc(MAX_ABBREVS*MAX_ABBREV_LENGTH,
        "abbreviations");
    abbrev_values    = my_calloc(sizeof(int), MAX_ABBREVS, "abbrev values");
    abbrev_quality   = my_calloc(sizeof(int), MAX_ABBREVS, "abbrev quality");
    abbrev_freqs     = my_calloc(sizeof(int),   MAX_ABBREVS, "abbrev freqs");

    dtree            = my_calloc(sizeof(dict_tree_node), MAX_DICT_ENTRIES,
                                 "red-black tree for dictionary");
    final_dict_order = my_calloc(sizeof(int),  MAX_DICT_ENTRIES,
                                 "final dictionary ordering table");
    dict_sort_codes  = my_calloc(DICT_WORD_BYTES, MAX_DICT_ENTRIES,
                                 "dictionary sort codes");

    if (!glulx_mode)
        dictionary = my_malloc(9*MAX_DICT_ENTRIES+7,
            "dictionary");
    else
        dictionary = my_malloc(DICT_ENTRY_BYTE_LENGTH*MAX_DICT_ENTRIES+4,
            "dictionary");

    strings_holding_area
         = my_malloc(MAX_STATIC_STRINGS,"static strings holding area");
    low_strings = my_malloc(MAX_LOW_STRINGS,"low (abbreviation) strings");

    huff_entities = NULL;
    hufflist = NULL;
    unicode_usage_entries = NULL;
    done_compression = FALSE;
    compression_table_size = 0;
    compressed_offsets = NULL;

    MAX_CHARACTER_SET = 0;

    if (glulx_mode) {
      if (compression_switch) {
        int ix;
        MAX_CHARACTER_SET = 257 + MAX_ABBREVS + MAX_DYNAMIC_STRINGS
          + MAX_UNICODE_CHARS;
        huff_entities = my_calloc(sizeof(huffentity_t), MAX_CHARACTER_SET*2+1,
          "huffman entities");
        hufflist = my_calloc(sizeof(huffentity_t *), MAX_CHARACTER_SET,
          "huffman node list");
        unicode_usage_entries = my_calloc(sizeof(unicode_usage_t),
          MAX_UNICODE_CHARS, "unicode entity entries");
        for (ix=0; ix<UNICODE_HASH_BUCKETS; ix++)
          unicode_usage_hash[ix] = NULL;
      }
      compressed_offsets = my_calloc(sizeof(int32), MAX_NUM_STATIC_STRINGS,
        "static strings index table");
    }
}
