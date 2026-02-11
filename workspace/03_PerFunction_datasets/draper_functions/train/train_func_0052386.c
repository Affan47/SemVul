relocate_htable(value_t oldv, value_t newv)
{
    htable_t *oldh = (htable_t*)cv_data((cvalue_t*)ptr(oldv));
    htable_t *h = (htable_t*)cv_data((cvalue_t*)ptr(newv));
    if (oldh->table == &oldh->_space[0])
        h->table = &h->_space[0];
    size_t i;
    for(i=0; i < h->size; i++) {
        if (h->table[i] != HT_NOTFOUND)
            h->table[i] = (void*)relocate_lispvalue((value_t)h->table[i]);
    }
}
