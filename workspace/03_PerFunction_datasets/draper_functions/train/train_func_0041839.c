_ssll_iterator_reset(ssll_iterator *it)
{
    sl_container *t;


    if(NULL == it) {
        netsnmp_assert(NULL != it);
        return 0;
    }

    if(NULL == it->base.container) {
        netsnmp_assert(NULL != it->base.container);
        return 0;
    }
    t = (sl_container *)it->base.container;
    if(NULL == t)
        return -1;

    it->last = NULL;
    it->pos = t->head;


    it->base.sync = it->base.container->sync;

    return 0;
}
