h_resample_fast4_mmx(uint8_t *dst, int dst_width,
                                 const uint8_t *src, int src_width,
                                 int src_start, int src_incr, int16_t *filters)
{
    int src_pos, phase;
    const uint8_t *s;
    int16_t *filter;
    uint64_t tmp;

    src_pos = src_start;
    pxor_r2r(mm7, mm7);

    while (dst_width >= 4) {

        FILTER4(mm0);
        FILTER4(mm1);
        FILTER4(mm2);
        FILTER4(mm3);

        packuswb_r2r(mm7, mm0);
        packuswb_r2r(mm7, mm1);
        packuswb_r2r(mm7, mm3);
        packuswb_r2r(mm7, mm2);
        movq_r2m(mm0, tmp);
        dst[0] = tmp & 0xFF;
        movq_r2m(mm1, tmp);
        dst[1] = tmp & 0xFF;
        movq_r2m(mm2, tmp);
        dst[2] = tmp & 0xFF;
        movq_r2m(mm3, tmp);
        dst[3] = tmp & 0xFF;
        dst += 4;
        dst_width -= 4;
    }
    while (dst_width > 0) {
        FILTER4(mm0);
        packuswb_r2r(mm7, mm0);
        movq_r2m(mm0, tmp);
        dst[0] = tmp & 0xFF;
        dst++;
        dst_width--;
    }
    emms();
}
