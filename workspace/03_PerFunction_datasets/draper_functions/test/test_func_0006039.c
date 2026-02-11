gxf_write_media_packet(ByteIOContext *pb, GXFContext *ctx, AVPacket *pkt)
{
    GXFStreamContext *sc = ctx->fc->streams[pkt->stream_index]->priv_data;
    int64_t pos = url_ftell(pb);
    int padding = 0;

    gxf_write_packet_header(pb, PKT_MEDIA);
    if (sc->codec->codec_id == CODEC_ID_MPEG2VIDEO && pkt->size % 4)
        padding = 4 - pkt->size % 4;
    else if (sc->codec->codec_type == CODEC_TYPE_AUDIO)
        padding = GXF_AUDIO_PACKET_SIZE - pkt->size;
    gxf_write_media_preamble(pb, ctx, pkt, pkt->size + padding);
    put_buffer(pb, pkt->data, pkt->size);
    gxf_write_padding(pb, padding);

    if (sc->codec->codec_type == CODEC_TYPE_VIDEO)
        ctx->nb_fields += 2;

    return updatePacketSize(pb, pos);
}
