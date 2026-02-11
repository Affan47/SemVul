mmf_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    MMFContext *mmf = s->priv_data;
    AVStream *st;
    int ret, size;

    if (url_feof(s->pb))
        return AVERROR(EIO);
    st = s->streams[0];

    size = MAX_SIZE;
    if(size > mmf->data_size)
        size = mmf->data_size;

    if(!size)
        return AVERROR(EIO);

    if (av_new_packet(pkt, size))
        return AVERROR(EIO);
    pkt->stream_index = 0;

    ret = get_buffer(s->pb, pkt->data, pkt->size);
    if (ret < 0)
        av_free_packet(pkt);

    mmf->data_size -= ret;

    pkt->size = ret;
    return ret;
}
