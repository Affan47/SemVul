msea_doc_freq(Searcher *self, const char *field, const char *term)
{
    int i;
    int doc_freq = 0;
    MultiSearcher *msea = MSEA(self);
    for (i = 0; i < msea->s_cnt; i++) {
        Searcher *s = msea->searchers[i];
        doc_freq += s->doc_freq(s, field, term);
    }

    return doc_freq;
}
