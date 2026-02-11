disjunction_sum_scorer_new(Scorer **sub_scorers, int ss_cnt,
                                          int min_num_matches)
{
    Scorer *self = scorer_new(DisjunctionSumScorer, NULL);
    DSSc(self)->ss_cnt = ss_cnt;


    self->doc = -1;
    DSSc(self)->cum_score = -1.0;


    DSSc(self)->num_matches = -1;
    DSSc(self)->coordinator = NULL;

#ifdef DEBUG
    if (min_num_matches <= 0) {
        RAISE(ARG_ERROR, "The min_num_matches value <%d> should not be less "
              "than 0\n", min_num_matches);
    }
    if (ss_cnt <= 1) {
        RAISE(ARG_ERROR, "There should be at least 2 sub_scorers in a "
              "DiscjunctionSumScorer. <%d> is not enough", ss_cnt);
    }
#endif

    DSSc(self)->min_num_matches = min_num_matches;
    DSSc(self)->sub_scorers     = sub_scorers;
    DSSc(self)->scorer_queue    = NULL;

    self->score   = &dssc_score;
    self->next    = &dssc_next;
    self->skip_to = &dssc_skip_to;
    self->explain = &dssc_explain;
    self->destroy = &dssc_destroy;

    return self;
}
