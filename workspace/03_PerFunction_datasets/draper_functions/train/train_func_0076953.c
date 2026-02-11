raw_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    int ret, size, bps;


    size= RAW_PACKET_SIZE;

    ret= av_get_packet(s->pb, pkt, size);

    pkt->stream_index = 0;
    if (ret <= 0) {
        return AVERROR(EIO);
    }


    pkt->size = ret;

    bps= av_get_bits_per_sample(s->streams[0]->codec->codec_id);
    assert(bps);
    pkt->dts=
    pkt->pts= pkt->pos*8 / (bps * s->streams[0]->codec->channels);

    return ret;
}
