ogm_packet(AVFormatContext *s, int idx)
{
    struct ogg *ogg = s->priv_data;
    struct ogg_stream *os = ogg->streams + idx;
    uint8_t *p = os->buf + os->pstart;
    int lb;

    if(*p & 8)
        os->pflags |= PKT_FLAG_KEY;

    lb = ((*p & 2) << 1) | ((*p >> 6) & 3);
    os->pstart += lb + 1;
    os->psize -= lb + 1;

    return 0;
}
