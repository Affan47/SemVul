tsc_explain(Scorer *self, int doc_num)
{
    TermScorer *ts = TSc(self);
    Query *query = ts->weight->get_query(ts->weight);
    int tf = 0;

    tsc_skip_to(self, doc_num);
    if (self->doc == doc_num) {
        tf = ts->freqs[ts->pointer];
    }
    return expl_new(sim_tf(self->similarity, (float)tf),
                    "tf(term_freq(%s:%s)=%d)",
                    TQ(query)->field, TQ(query)->term, tf);
}
