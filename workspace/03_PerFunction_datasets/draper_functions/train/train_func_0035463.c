ff_msmpeg4_encode_motion(MpegEncContext * s,
                                  int mx, int my)
{
    int code;
    MVTable *mv;


    if (mx <= -64)
        mx += 64;
    else if (mx >= 64)
        mx -= 64;
    if (my <= -64)
        my += 64;
    else if (my >= 64)
        my -= 64;

    mx += 32;
    my += 32;
#if 0
    if ((unsigned)mx >= 64 ||
        (unsigned)my >= 64)
        av_log(s->avctx, AV_LOG_ERROR, "error mx=%d my=%d\n", mx, my);
#endif
    mv = &mv_tables[s->mv_table_index];

    code = mv->table_mv_index[(mx << 6) | my];
    put_bits(&s->pb,
             mv->table_mv_bits[code],
             mv->table_mv_code[code]);
    if (code == mv->n) {

        put_bits(&s->pb, 6, mx);
        put_bits(&s->pb, 6, my);
    }
}
