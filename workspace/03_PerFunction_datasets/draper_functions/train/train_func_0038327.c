predictor_decode_stereo(APEContext * ctx, int count)
{
    int32_t predictionA, predictionB;
    APEPredictor *p = &ctx->predictor;
    int32_t *decoded0 = ctx->decoded0;
    int32_t *decoded1 = ctx->decoded1;

    while (count--) {

        predictionA = predictor_update_filter(p, *decoded0, 0, YDELAYA, YDELAYB, YADAPTCOEFFSA, YADAPTCOEFFSB);
        predictionB = predictor_update_filter(p, *decoded1, 1, XDELAYA, XDELAYB, XADAPTCOEFFSA, XADAPTCOEFFSB);
        *(decoded0++) = predictionA;
        *(decoded1++) = predictionB;


        p->buf++;


        if (p->buf == p->historybuffer + HISTORY_SIZE) {
            memmove(p->historybuffer, p->buf, PREDICTOR_SIZE * sizeof(int32_t));
            p->buf = p->historybuffer;
        }
    }
}
