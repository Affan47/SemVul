searcher_get_match_vector(Searcher *self,
                                       Query *query,
                                       const int doc_num,
                                       const char *field)
{
    MatchVector *mv = matchv_new();
    Query *rewritten_query = self->rewrite(self, query);
    TermVector *tv = self->get_term_vector(self, doc_num, field);
    if (tv && tv->term_cnt > 0 && tv->terms[0].positions != NULL) {
        mv = rewritten_query->get_matchv_i(rewritten_query, mv, tv);
        tv_destroy(tv);
    }
    q_deref(rewritten_query);
    return mv;
}
