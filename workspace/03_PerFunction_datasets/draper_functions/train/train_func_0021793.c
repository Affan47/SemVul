iss_read_packet(AVFormatContext *s, AVPacket *pkt)
{
    IssDemuxContext *iss = s->priv_data;
    int ret = av_get_packet(s->pb, pkt, iss->packet_size);

    if(ret != iss->packet_size)
        return AVERROR(EIO);

    pkt->stream_index = 0;
    pkt->pts = url_ftell(s->pb) - iss->sample_start_pos;
    if(s->streams[0]->codec->channels > 0)
        pkt->pts /= s->streams[0]->codec->channels*2;
    return 0;
}
