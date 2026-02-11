abq_push_tslf(dns_abq_base_t *abqb, void *elem)
{
    unsigned wcur, wpos;
    volatile dns_abq_base_t *v = (volatile dns_abq_base_t *) abqb;

    for (;;) {
        if (v->abqb_wcursor == v->abqb_rcursor + v->abqb_max) {
            if (abq_radv_tslf(abqb) < 0)
                return -1;
            continue;
        }

        wcur = v->abqb_wcursor;
        wpos = wcur % v->abqb_max;

        if (v->abqb_aptr[wpos] != NULL) {
            ATOMIC_CAS(&v->abqb_wcursor, wcur, wcur + 1);
        } else {
            if (ATOMIC_CAS_PTR(&v->abqb_aptr[wpos], NULL, elem)) {
                ATOMIC_CAS(&v->abqb_wcursor, wcur, wcur + 1);
                return 0;
            }
        }
    }
}
