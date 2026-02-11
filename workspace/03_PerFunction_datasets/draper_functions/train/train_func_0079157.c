encode_residual_v(FlacEncodeContext *ctx, int ch)
{
    int i, n;
    FlacFrame *frame;
    FlacSubframe *sub;
    int32_t *res, *smp;

    frame = &ctx->frame;
    sub = &frame->subframes[ch];
    res = sub->residual;
    smp = sub->samples;
    n = frame->blocksize;


    for(i=1; i<n; i++) {
        if(smp[i] != smp[0]) break;
    }
    if(i == n) {
        sub->type = sub->type_code = FLAC_SUBFRAME_CONSTANT;
        res[0] = smp[0];
        return sub->obits;
    }


    sub->type = sub->type_code = FLAC_SUBFRAME_VERBATIM;
    encode_residual_verbatim(res, smp, n);
    return sub->obits * n;
}
