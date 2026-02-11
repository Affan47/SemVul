spanmtq_get_terms(Query *self)
{
    HashSet *terms = hs_new_str(&free);
    SpanMultiTermQuery *smtq = SpMTQ(self);
    int i;
    for (i = 0; i < smtq->term_cnt; i++) {
        hs_add(terms, estrdup(smtq->terms[i]));
    }
    return terms;
}
