dsputil_init_pix_mmx(DSPContext* c, AVCodecContext *avctx)
{
    if (mm_flags & FF_MM_MMX) {
        c->pix_abs[0][0] = sad16_mmx;
        c->pix_abs[0][1] = sad16_x2_mmx;
        c->pix_abs[0][2] = sad16_y2_mmx;
        c->pix_abs[0][3] = sad16_xy2_mmx;
        c->pix_abs[1][0] = sad8_mmx;
        c->pix_abs[1][1] = sad8_x2_mmx;
        c->pix_abs[1][2] = sad8_y2_mmx;
        c->pix_abs[1][3] = sad8_xy2_mmx;

        c->sad[0]= sad16_mmx;
        c->sad[1]= sad8_mmx;
    }
    if (mm_flags & FF_MM_MMXEXT) {
        c->pix_abs[0][0] = sad16_mmx2;
        c->pix_abs[1][0] = sad8_mmx2;

        c->sad[0]= sad16_mmx2;
        c->sad[1]= sad8_mmx2;

        if(!(avctx->flags & CODEC_FLAG_BITEXACT)){
            c->pix_abs[0][1] = sad16_x2_mmx2;
            c->pix_abs[0][2] = sad16_y2_mmx2;
            c->pix_abs[0][3] = sad16_xy2_mmx2;
            c->pix_abs[1][1] = sad8_x2_mmx2;
            c->pix_abs[1][2] = sad8_y2_mmx2;
            c->pix_abs[1][3] = sad8_xy2_mmx2;
        }
    }
    if ((mm_flags & FF_MM_SSE2) && !(mm_flags & FF_MM_3DNOW)) {
        c->sad[0]= sad16_sse2;
    }
}
