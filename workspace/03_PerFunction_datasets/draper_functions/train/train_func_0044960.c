simdef_idf_phrase(struct Similarity *s, const char *field,
                        PhrasePosition *positions,
                        int pp_cnt, Searcher *searcher)
{
    float idf = 0.0;
    int i, j;
    for (i = 0; i < pp_cnt; i++) {
        char **terms = positions[i].terms;
        for (j = ary_size(terms) - 1; j >= 0; j--) {
            idf += sim_idf_term(s, field, terms[j], searcher);
        }
    }
    return idf;
}
