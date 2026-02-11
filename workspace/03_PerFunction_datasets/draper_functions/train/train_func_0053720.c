abq_pop_tus(dns_abq_base_t *abqb)
{
    void *p;
    unsigned rpos;

    if (abqb->abqb_rcursor == abqb->abqb_wcursor)
        return NULL;

    rpos = abqb->abqb_rcursor % abqb->abqb_max;
    p = abqb->abqb_aptr[rpos];
    abqb->abqb_aptr[rpos] = NULL;
    abqb->abqb_rcursor++;

    return p;
}
