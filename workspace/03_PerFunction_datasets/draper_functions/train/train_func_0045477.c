ntru_equals1(NtruIntPoly *p) {
    int i;
    for (i=1; i<p->N; i++)
        if (p->coeffs[i] != 0)
            return 0;
    return p->coeffs[0] == 1;
}
