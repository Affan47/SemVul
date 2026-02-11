ntru_gen_blind_poly(uint8_t *seed, uint16_t seed_len, NtruEncParams *params, NtruPrivPoly *r) {
    NtruIGFState s;
    ntru_IGF_init(seed, seed_len, params, &s);

#ifndef NTRU_AVOID_HAMMING_WT_PATENT
    if (params->prod_flag) {
        r->poly.prod.N = s.N;
        ntru_gen_tern_poly(&s, params->df1, &r->poly.prod.f1);
        ntru_gen_tern_poly(&s, params->df2, &r->poly.prod.f2);
        ntru_gen_tern_poly(&s, params->df3, &r->poly.prod.f3);
    }
    else
#endif
    {
        r->poly.tern.N = s.N;
        ntru_gen_tern_poly(&s, params->df1, &r->poly.tern);
    }
}
