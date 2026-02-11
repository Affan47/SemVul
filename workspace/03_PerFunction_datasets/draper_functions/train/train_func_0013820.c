ntru_check_rep_weight(NtruIntPoly *p, uint16_t dm0) {
    uint16_t i;
    uint16_t weights[3];
    weights[0] = weights[1] = weights[2] = 0;

    for (i=0; i<p->N; i++)
        weights[p->coeffs[i]]++;

    return (weights[0]>=dm0 && weights[1]>=dm0 && weights[2]>=dm0);
}
