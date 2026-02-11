phq_hash(Query *self)
{
    int i, j;
    PhraseQuery *phq = PhQ(self);
    unsigned long hash = sym_hash(phq->field);
    for (i = 0; i < phq->pos_cnt; i++) {
        char **terms = phq->positions[i].terms;
        for (j = ary_size(terms) - 1; j >= 0; j--) {
            hash = (hash << 1) ^ (str_hash(terms[j])
                               ^ phq->positions[i].pos);
        }
    }
    return (hash ^ phq->slop);
}
