dct_get(ASV1Context *a, int mb_x, int mb_y){
    DCTELEM (*block)[64]= a->block;
    int linesize= a->picture.linesize[0];
    int i;

    uint8_t *ptr_y  = a->picture.data[0] + (mb_y * 16* linesize              ) + mb_x * 16;
    uint8_t *ptr_cb = a->picture.data[1] + (mb_y * 8 * a->picture.linesize[1]) + mb_x * 8;
    uint8_t *ptr_cr = a->picture.data[2] + (mb_y * 8 * a->picture.linesize[2]) + mb_x * 8;

    a->dsp.get_pixels(block[0], ptr_y                 , linesize);
    a->dsp.get_pixels(block[1], ptr_y              + 8, linesize);
    a->dsp.get_pixels(block[2], ptr_y + 8*linesize    , linesize);
    a->dsp.get_pixels(block[3], ptr_y + 8*linesize + 8, linesize);
    for(i=0; i<4; i++)
        a->dsp.fdct(block[i]);

    if(!(a->avctx->flags&CODEC_FLAG_GRAY)){
        a->dsp.get_pixels(block[4], ptr_cb, a->picture.linesize[1]);
        a->dsp.get_pixels(block[5], ptr_cr, a->picture.linesize[2]);
        for(i=4; i<6; i++)
            a->dsp.fdct(block[i]);
    }
}
