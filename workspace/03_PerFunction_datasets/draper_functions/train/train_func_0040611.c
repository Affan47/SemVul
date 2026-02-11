do_apply_filter(APEContext * ctx, int version, APEFilter *f, int32_t *data, int count, int order, int fracbits)
{
    int res;
    int absres;

    while (count--) {

        res = (ctx->dsp.scalarproduct_int16(f->delay - order, f->coeffs, order, 0) + (1 << (fracbits - 1))) >> fracbits;

        if (*data < 0)
            ctx->dsp.add_int16(f->coeffs, f->adaptcoeffs - order, order);
        else if (*data > 0)
            ctx->dsp.sub_int16(f->coeffs, f->adaptcoeffs - order, order);

        res += *data;

        *data++ = res;


        *f->delay++ = av_clip_int16(res);

        if (version < 3980) {

            f->adaptcoeffs[0]  = (res == 0) ? 0 : ((res >> 28) & 8) - 4;
            f->adaptcoeffs[-4] >>= 1;
            f->adaptcoeffs[-8] >>= 1;
        } else {


            absres = (res < 0 ? -res : res);

            if (absres > (f->avg * 3))
                *f->adaptcoeffs = ((res >> 25) & 64) - 32;
            else if (absres > (f->avg * 4) / 3)
                *f->adaptcoeffs = ((res >> 26) & 32) - 16;
            else if (absres > 0)
                *f->adaptcoeffs = ((res >> 27) & 16) - 8;
            else
                *f->adaptcoeffs = 0;

            f->avg += (absres - f->avg) / 16;

            f->adaptcoeffs[-1] >>= 1;
            f->adaptcoeffs[-2] >>= 1;
            f->adaptcoeffs[-8] >>= 1;
        }

        f->adaptcoeffs++;


        if (f->delay == f->historybuffer + HISTORY_SIZE + (order * 2)) {
            memmove(f->historybuffer, f->delay - (order * 2),
                    (order * 2) * sizeof(int16_t));
            f->delay = f->historybuffer + order * 2;
            f->adaptcoeffs = f->historybuffer + order;
        }
    }
}
