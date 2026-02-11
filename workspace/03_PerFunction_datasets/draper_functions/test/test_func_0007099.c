abq_pop_tslf(dns_abq_base_t *abqb)
{
    void *p;
    unsigned rcur, rpos;
    volatile dns_abq_base_t *v = (volatile dns_abq_base_t *) abqb;

    for (;;) {
        if (v->abqb_rcursor == v->abqb_wcursor) {
            if (abq_wadv_tslf(abqb) < 0)
                return NULL;
            continue;
        }

        rcur = v->abqb_rcursor;
        rpos = rcur % v->abqb_max;

        if ((p = v->abqb_aptr[rpos]) == NULL)
            ATOMIC_CAS(&v->abqb_rcursor, rcur, rcur + 1);
        else {
            if (ATOMIC_CAS_PTR(&v->abqb_aptr[rpos], p, NULL)) {
                ATOMIC_CAS(&v->abqb_rcursor, rcur, rcur + 1);
                return p;
            }
        }
    }
}
