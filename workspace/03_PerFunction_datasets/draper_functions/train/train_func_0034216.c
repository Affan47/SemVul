ntru_mult_prod(NtruIntPoly *a, NtruProdPoly *b, NtruIntPoly *c, uint16_t modulus) {
    uint16_t N = a->N;
    if (N != b->N)
        return 0;
    c->N = N;
    memset(&c->coeffs, 0, N * sizeof c->coeffs[0]);

    NtruIntPoly temp;
    ntru_mult_tern(a, &b->f1, &temp, modulus);
    ntru_mult_tern(&temp, &b->f2, c, modulus);
    NtruIntPoly f3a;
    ntru_mult_tern(a, &b->f3, &f3a, modulus);
    ntru_add_int(c, &f3a);

    ntru_mod(c, modulus);
    return 1;
}
