encode_buffer (
    PCX_INST *g,
    BYTE     *inbuf_p,
    BYTE     *outbuf_p)
{
    BYTE *out_p;
    BYTE *beg_run_p;
    BYTE *aft_run_p;
    BYTE *inbuf_aft_p;
    BYTE  byt;
    UINT  run_len;

    out_p = outbuf_p;
    beg_run_p = inbuf_p;
    inbuf_aft_p = inbuf_p + g->uBytesPerPlane * g->traits.iBitsPerPixel;

    while (beg_run_p < inbuf_aft_p)
    {
        byt = *beg_run_p;

        for (aft_run_p = beg_run_p+1;
             aft_run_p<inbuf_aft_p && *aft_run_p==byt;
             aft_run_p++) ;

        run_len = aft_run_p - beg_run_p;
        if (run_len > 63) {
            run_len = 63;
            aft_run_p = beg_run_p + 63;
        }

        if (run_len>1 || byt>=(BYTE)0xc0)
            *out_p++ = (BYTE)run_len | (BYTE)0xc0;
        *out_p++ = byt;

        beg_run_p = aft_run_p;
    }

    return out_p - outbuf_p;
}
