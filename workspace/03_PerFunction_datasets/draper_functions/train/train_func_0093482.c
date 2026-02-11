thp_read_packet(AVFormatContext *s,
                            AVPacket *pkt)
{
    ThpDemuxContext *thp = s->priv_data;
    ByteIOContext *pb = s->pb;
    int size;
    int ret;

    if (thp->audiosize == 0) {

        if (thp->frame >= thp->framecnt)
            return AVERROR(EIO);

        url_fseek(pb, thp->next_frame, SEEK_SET);


        thp->next_frame += thp->next_framesz;
        thp->next_framesz = get_be32(pb);

                        get_be32(pb);
        size          = get_be32(pb);


        if (thp->has_audio)
            thp->audiosize = get_be32(pb);
        else
            thp->frame++;

        ret = av_get_packet(pb, pkt, size);
        if (ret != size) {
            av_free_packet(pkt);
            return AVERROR(EIO);
        }

        pkt->stream_index = thp->video_stream_index;
    } else {
        ret = av_get_packet(pb, pkt, thp->audiosize);
        if (ret != thp->audiosize) {
            av_free_packet(pkt);
            return AVERROR(EIO);
        }

        pkt->stream_index = thp->audio_stream_index;
        thp->audiosize = 0;
        thp->frame++;
    }

    return 0;
}
