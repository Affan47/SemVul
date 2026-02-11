trie_state_walkable_chars (const TrieState  *s,
                           AlphaChar         chars[],
                           int               chars_nelm)
{
    int syms_num = 0;

    if (!s->is_suffix) {
        Symbols *syms = da_output_symbols (s->trie->da, s->index);
        int i;

        syms_num = symbols_num (syms);
        for (i = 0; i < syms_num && i < chars_nelm; i++) {
            TrieChar tc = symbols_get (syms, i);
            chars[i] = alpha_map_trie_to_char (s->trie->alpha_map, tc);
        }

        symbols_free (syms);
    } else {
        const TrieChar *suffix = tail_get_suffix (s->trie->tail, s->index);
        chars[0] = alpha_map_trie_to_char (s->trie->alpha_map,
                                           suffix[s->suffix_idx]);
        syms_num = 1;
    }

    return syms_num;
}
