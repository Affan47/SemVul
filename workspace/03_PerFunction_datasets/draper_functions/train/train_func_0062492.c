SHRotateZ(const Spectrum *c_in, Spectrum *c_out, float alpha,
               int lmax) {
    Assert(c_in != c_out);
    c_out[0] = c_in[0];
    if (lmax == 0) return;

    float *ct = ALLOCA(float, lmax+1);
    float *st = ALLOCA(float, lmax+1);
    sinCosIndexed(sinf(alpha), cosf(alpha), lmax+1, st, ct);
    for (int l = 1; l <= lmax; ++l) {

        for (int m = -l; m < 0; ++m)
            c_out[SHIndex(l, m)] =
                ( ct[-m] * c_in[SHIndex(l,  m)] +
                 -st[-m] * c_in[SHIndex(l, -m)]);
        c_out[SHIndex(l, 0)] = c_in[SHIndex(l, 0)];
        for (int m = 1; m <= l; ++m)
            c_out[SHIndex(l, m)] =
                (ct[m] * c_in[SHIndex(l,  m)] +
                 st[m] * c_in[SHIndex(l, -m)]);
    }
}
