ntru_gen_tern_poly(NtruIGFState *s, uint16_t df, NtruTernPoly *p) {
    p->N = s->N;
    p->num_ones = df;
    p->num_neg_ones = df;

    uint16_t idx;
    uint16_t r[p->N];
    memset(r, 0, sizeof r);

    uint16_t t = 0;
    while (t < df) {
        ntru_IGF_next(s, &idx);
        if (!r[idx]) {
            p->neg_ones[t] = idx;
            r[idx] = 1;
            t++;
        }
    }
    t = 0;
    while (t < df) {
        ntru_IGF_next(s, &idx);
        if (!r[idx]) {
            p->ones[t] = idx;
            r[idx] = 1;
            t++;
        }
    }
}
