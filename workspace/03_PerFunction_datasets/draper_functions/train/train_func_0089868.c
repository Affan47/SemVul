art_pdf_recomposite_group_8(byte *dst, byte *dst_alpha_g,
        const byte *src, byte src_alpha_g, int n_chan,
        byte alpha, gs_blend_mode_t blend_mode,
        const pdf14_nonseparable_blending_procs_t * pblend_procs)
{
    byte dst_alpha;
    int i;
    int tmp;
    int scale;

    if (src_alpha_g == 0)
        return;

    if (blend_mode == BLEND_MODE_Normal && alpha == 255) {


        memcpy(dst, src, n_chan + 1);
        if (dst_alpha_g != NULL) {
            tmp = (255 - *dst_alpha_g) * (255 - src_alpha_g) + 0x80;
            *dst_alpha_g = 255 - ((tmp + (tmp >> 8)) >> 8);
        }
        return;
    } else {

        byte ca[ART_MAX_CHAN + 1];

        dst_alpha = dst[n_chan];
        if (src_alpha_g == 255 || dst_alpha == 0) {
            memcpy(ca, src, n_chan + 3);
        } else {


            scale = (dst_alpha * 255 * 2 + src_alpha_g) / (src_alpha_g << 1) -
                dst_alpha;
            for (i = 0; i < n_chan; i++) {
                int si, di;

                si = src[i];
                di = dst[i];
                tmp = (si - di) * scale + 0x80;
                tmp = si + ((tmp + (tmp >> 8)) >> 8);


                if (tmp < 0)
                    tmp = 0;
                if (tmp > 255)
                    tmp = 255;
                ca[i] = tmp;
            }
        }

        tmp = src_alpha_g * alpha + 0x80;
        tmp = (tmp + (tmp >> 8)) >> 8;
        ca[n_chan] = tmp;
        if (dst_alpha_g != NULL) {
            tmp = (255 - *dst_alpha_g) * (255 - tmp) + 0x80;
            *dst_alpha_g = 255 - ((tmp + (tmp >> 8)) >> 8);
        }
        art_pdf_composite_pixel_alpha_8(dst, ca, n_chan,
                                        blend_mode, pblend_procs);
    }

}
