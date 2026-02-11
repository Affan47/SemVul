phq_destroy(Query *self)
{
    PhraseQuery *phq = PhQ(self);
    int i;
    for (i = 0; i < phq->pos_cnt; i++) {
        ary_destroy(phq->positions[i].terms, &free);
    }
    free(phq->positions);
    q_destroy_i(self);
}
