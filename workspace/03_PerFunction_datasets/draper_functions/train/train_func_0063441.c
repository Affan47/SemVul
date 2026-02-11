SHEvaluate(const Vector &w, int lmax, float *out) {
    if (lmax > 28)
        Severe("SHEvaluate() runs out of numerical precision for lmax > 28. "
               "If you need more bands, try recompiling using doubles.");

    Assert(w.Length() > .995f && w.Length() < 1.005f);
    legendrep(w.z, lmax, out);


    float *Klm = ALLOCA(float, SHTerms(lmax));
    for (int l = 0; l <= lmax; ++l)
        for (int m = -l; m <= l; ++m)
            Klm[SHIndex(l, m)] = K(l, m);


    float *sins = ALLOCA(float, lmax+1), *coss = ALLOCA(float, lmax+1);
    float xyLen = sqrtf(max(0.f, 1.f - w.z*w.z));
    if (xyLen == 0.f) {
        for (int i = 0; i <= lmax; ++i) sins[i] = 0.f;
        for (int i = 0; i <= lmax; ++i) coss[i] = 1.f;
    }
    else
        sinCosIndexed(w.y / xyLen, w.x / xyLen, lmax+1, sins, coss);


    static const float sqrt2 = sqrtf(2.f);
    for (int l = 0; l <= lmax; ++l) {
        for (int m = -l; m < 0; ++m)
        {
            out[SHIndex(l, m)] = sqrt2 * Klm[SHIndex(l, m)] *
                out[SHIndex(l, -m)] * sins[-m];
            Assert(!isnan(out[SHIndex(l,m)]));
            Assert(!isinf(out[SHIndex(l,m)]));
        }
        out[SHIndex(l, 0)] *= Klm[SHIndex(l, 0)];
        for (int m = 1; m <= l; ++m)
        {
            out[SHIndex(l, m)] *= sqrt2 * Klm[SHIndex(l, m)] * coss[m];
            Assert(!isnan(out[SHIndex(l,m)]));
            Assert(!isinf(out[SHIndex(l,m)]));
        }
    }
}
