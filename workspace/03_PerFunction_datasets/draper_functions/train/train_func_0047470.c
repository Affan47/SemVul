ff_fft_permute_c(FFTContext *s, FFTComplex *z)
{
    int j, k, np;
    FFTComplex tmp;
    const uint16_t *revtab = s->revtab;
    np = 1 << s->nbits;

    if (s->tmp_buf) {

        for(j=0;j<np;j++) s->tmp_buf[revtab[j]] = z[j];
        memcpy(z, s->tmp_buf, np * sizeof(FFTComplex));
        return;
    }


    for(j=0;j<np;j++) {
        k = revtab[j];
        if (k < j) {
            tmp = z[k];
            z[k] = z[j];
            z[j] = tmp;
        }
    }
}
