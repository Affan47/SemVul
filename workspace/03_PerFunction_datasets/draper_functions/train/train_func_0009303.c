snd_sref_inverse(sound_type s, double val)
{
    double exact_cnt;
    int i;
    sample_block_type sampblock;
    long blocklen;
    sample_type x1, x2;

    if (val < 0) {
        xlcerror("return 0", "negative value", cvflonum(val));
        return 0.0;
    }
    s = sound_copy(s);

    x1 = 0.0F;

    while (true) {
        sampblock = sound_get_next(s, &blocklen);
        x2 = sampblock->samples[blocklen - 1];
        if (x2 >= val) break;
        x1 = x2;
        if (sampblock == zero_block) {
            xlcerror("return 0", "too large, no inverse", cvflonum(val));
            sound_unref(s);
            return 0.0;
        }
    }


    for (i = 0; i < blocklen && sampblock->samples[i] <= val; i++) ;


    if (i > 1) x1 = sampblock->samples[i - 1];
    x2 = sampblock->samples[i];


    if (x2 == x1) exact_cnt = 0;
    else exact_cnt = (val - x1) / (x2 - x1);


    exact_cnt += (s->current - blocklen) + (i - 1);


    if (exact_cnt < 0) exact_cnt = 0;


    exact_cnt = s->t0 + exact_cnt / s->sr;

    sound_unref(s);
    return exact_cnt;
}
