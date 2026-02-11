dv_write_packet(struct AVFormatContext *s, AVPacket *pkt)
{
    uint8_t* frame;
    int fsize;

    fsize = dv_assemble_frame(s->priv_data, s->streams[pkt->stream_index],
                              pkt->data, pkt->size, &frame);
    if (fsize > 0) {
        put_buffer(s->pb, frame, fsize);
        put_flush_packet(s->pb);
    }
    return 0;
}
