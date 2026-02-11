compute_normed_power(gint16 *in_data, guint num_samples, gint *inout_prior)
{
    guint i, shift, sumsq, prior;

    sumsq = 0;
    shift = 0;
    prior = *inout_prior;
    for (i = 0; i < num_samples; ++i) {
        guint sq;
        gint x;


        x = in_data[i] - prior;
        prior = in_data[i];
        sq = x * x;
        sumsq += (sq >> shift);

        while (sumsq > 0x10000) {
            sumsq >>= 1;
            shift += 1;
        }
    }
    *inout_prior = prior;


    if (shift > 15)
        return (sumsq << (shift - 15)) / num_samples;
    else
        return (sumsq / num_samples) >> (15 - shift);
}
