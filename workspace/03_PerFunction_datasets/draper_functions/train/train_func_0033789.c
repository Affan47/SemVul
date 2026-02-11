sol_read_packet(AVFormatContext *s,
                          AVPacket *pkt)
{
    int ret;

    if (url_feof(s->pb))
        return AVERROR(EIO);
    ret= av_get_packet(s->pb, pkt, MAX_SIZE);
    pkt->stream_index = 0;


    pkt->size = ret;
    return 0;
}
