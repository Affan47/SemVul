ntru_clear_priv(NtruPrivPoly *p) {
#ifndef NTRU_AVOID_HAMMING_WT_PATENT
    if (p->prod_flag) {
        ntru_clear_tern(&p->poly.prod.f1);
        ntru_clear_tern(&p->poly.prod.f2);
        ntru_clear_tern(&p->poly.prod.f3);
    }
    else
#endif
        ntru_clear_tern(&p->poly.tern);
}
