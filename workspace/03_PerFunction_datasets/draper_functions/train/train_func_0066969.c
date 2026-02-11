fill_buffer(lame_global_flags const *gfp,
            sample_t * mfbuf[2], sample_t const *in_buffer[2], int nsamples, int *n_in, int *n_out)
{
    lame_internal_flags const *const gfc = gfp->internal_flags;
    int     ch, i;


    if ((gfc->resample_ratio < .9999) || (gfc->resample_ratio > 1.0001)) {
        for (ch = 0; ch < gfc->channels_out; ch++) {
            *n_out =
                fill_buffer_resample(gfp, &mfbuf[ch][gfc->mf_size],
                                     gfp->framesize, in_buffer[ch], nsamples, n_in, ch);
        }
    }
    else {
        *n_out = Min(gfp->framesize, nsamples);
        *n_in = *n_out;
        for (i = 0; i < *n_out; ++i) {
            mfbuf[0][gfc->mf_size + i] = in_buffer[0][i];
            if (gfc->channels_out == 2)
                mfbuf[1][gfc->mf_size + i] = in_buffer[1][i];
        }
    }
}
