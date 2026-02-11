multi_tq_to_s(Query *self, Symbol default_field)
{
    int i;
    PriorityQueue *boosted_terms = MTQ(self)->boosted_terms, *bt_pq_clone;
    BoostedTerm *bt;
    char *buffer, *bptr;
    const char *field = S(MTQ(self)->field);
    int flen = (int)strlen(field);
    int tlen = 0;


    for (i = boosted_terms->size; i > 0; i--) {
        tlen += (int)strlen(((BoostedTerm *)boosted_terms->heap[i])->term) + 35;
    }

    bptr = buffer = ALLOC_N(char, tlen + flen + 35);

    if (default_field != MTQ(self)->field) {
        bptr += sprintf(bptr, "%s:", field);
    }

    *(bptr++) = '"';
    bt_pq_clone = pq_clone(boosted_terms);
    while ((bt = (BoostedTerm *)pq_pop(bt_pq_clone)) != NULL) {
        bptr += sprintf(bptr, "%s", bt->term);

        if (bt->boost != 1.0) {
            *bptr = '^';
            dbl_to_s(++bptr, bt->boost);
            bptr += (int)strlen(bptr);
        }

        *(bptr++) = '|';
    }
    pq_destroy(bt_pq_clone);

    if (bptr[-1] == '"') {
        bptr++;
    }
    bptr[-1] =  '"';
    bptr[ 0] = '\0';

    if (self->boost != 1.0) {
        *bptr = '^';
        dbl_to_s(++bptr, self->boost);
    }

    return buffer;
}
