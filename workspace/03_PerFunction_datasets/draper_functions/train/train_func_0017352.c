vmd_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    VmdDemuxContext *vmd = s->priv_data;
    ByteIOContext *pb = s->pb;
    int ret = 0;
    vmd_frame *frame;

    if (vmd->current_frame >= vmd->frame_count)
        return AVERROR(EIO);

    frame = &vmd->frame_table[vmd->current_frame];

    url_fseek(pb, frame->frame_offset, SEEK_SET);

    if (av_new_packet(pkt, frame->frame_size + BYTES_PER_FRAME_RECORD))
        return AVERROR(ENOMEM);
    pkt->pos= url_ftell(pb);
    memcpy(pkt->data, frame->frame_record, BYTES_PER_FRAME_RECORD);
    if(vmd->is_indeo3)
        ret = get_buffer(pb, pkt->data, frame->frame_size);
    else
        ret = get_buffer(pb, pkt->data + BYTES_PER_FRAME_RECORD,
            frame->frame_size);

    if (ret != frame->frame_size) {
        av_free_packet(pkt);
        ret = AVERROR(EIO);
    }
    pkt->stream_index = frame->stream_index;
    pkt->pts = frame->pts;
    av_log(s, AV_LOG_DEBUG, " dispatching %s frame with %d bytes and pts %"PRId64"\n",
            (frame->frame_record[0] == 0x02) ? "video" : "audio",
            frame->frame_size + BYTES_PER_FRAME_RECORD,
            pkt->pts);

    vmd->current_frame++;

    return ret;
}
