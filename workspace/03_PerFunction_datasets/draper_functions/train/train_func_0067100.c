mult(ST_base_vector * in, ST_base_vector * out) {
    int    i;
    float *pm = &m[0][0];

    for (i = ST_MAX_BASE - 1; i >= 0; i--) {
        double sum0 = pm[4] * in->b[0];
        double sum1 = pm[3] * in->b[1];
        double sum2 = pm[2] * in->b[2];
        double sum3 = pm[1] * in->b[3];
        double sum4 = pm[0] * in->b[4];

        pm        += ST_MAX_BASE;
        out->b[i]  = (sum0 + sum1) + sum4 + (sum2 + sum3);
    }
    out->ld_lik = in->ld_lik;
    out->lik = in->lik;
}
