ra288_decode_frame(AVCodecContext * avctx, void *data,
                              int *data_size, const uint8_t * buf,
                              int buf_size)
{
    float *out = data;
    int i, j;
    RA288Context *ractx = avctx->priv_data;
    GetBitContext gb;

    if (buf_size < avctx->block_align) {
        av_log(avctx, AV_LOG_ERROR,
               "Error! Input buffer is too small [%d<%d]\n",
               buf_size, avctx->block_align);
        return 0;
    }

    if (*data_size < 32*5*4)
        return -1;

    init_get_bits(&gb, buf, avctx->block_align * 8);

    for (i=0; i < 32; i++) {
        float gain = amptable[get_bits(&gb, 3)];
        int cb_coef = get_bits(&gb, 6 + (i&1));

        decode(ractx, gain, cb_coef);

        for (j=0; j < 5; j++)
            *(out++) = ractx->sp_hist[70 + 36 + j];

        if ((i & 7) == 3) {
            backward_filter(ractx->sp_hist, ractx->sp_rec, syn_window,
                            ractx->sp_lpc, syn_bw_tab, 36, 40, 35, 70);

            backward_filter(ractx->gain_hist, ractx->gain_rec, gain_window,
                            ractx->gain_lpc, gain_bw_tab, 10, 8, 20, 28);
        }
    }

    *data_size = (char *)out - (char *)data;
    return avctx->block_align;
}
