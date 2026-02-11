abq_push_tus(dns_abq_base_t *abqb, void *elem)
{
    unsigned wpos;

    if (abqb->abqb_wcursor == abqb->abqb_rcursor + abqb->abqb_max)
        return -1;

    wpos = abqb->abqb_wcursor % abqb->abqb_max;
    abqb->abqb_aptr[wpos] = elem;
    abqb->abqb_wcursor++;

    return 0;
}
