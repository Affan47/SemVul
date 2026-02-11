bw_scorer(Weight *self, IndexReader *ir)
{
    Scorer *bsc = bsc_new(self->similarity);
    BooleanQuery *bq = BQ(self->query);
    int i;

    for (i = 0; i < BW(self)->w_cnt; i++) {
        BooleanClause *clause = bq->clauses[i];
        Weight *weight = BW(self)->weights[i];
        Scorer *sub_scorer = weight->scorer(weight, ir);
        if (sub_scorer) {
            bsc_add_scorer(bsc, sub_scorer, clause->occur);
        }
        else if (clause->is_required) {
            bsc->destroy(bsc);
            return NULL;
        }
    }

    return bsc;
}
