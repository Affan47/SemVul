wv_read_packet(AVFormatContext *s,
                          AVPacket *pkt)
{
    WVContext *wc = s->priv_data;
    int ret;

    if (url_feof(s->pb))
        return AVERROR(EIO);
    if(wc->block_parsed){
        if(wv_read_block_header(s, s->pb) < 0)
            return -1;
    }

    if(av_new_packet(pkt, wc->blksize + WV_EXTRA_SIZE) < 0)
        return AVERROR(ENOMEM);
    memcpy(pkt->data, wc->extra, WV_EXTRA_SIZE);
    ret = get_buffer(s->pb, pkt->data + WV_EXTRA_SIZE, wc->blksize);
    if(ret != wc->blksize){
        av_free_packet(pkt);
        return AVERROR(EIO);
    }
    pkt->stream_index = 0;
    wc->block_parsed = 1;
    pkt->size = ret + WV_EXTRA_SIZE;
    pkt->pts = wc->soff;
    av_add_index_entry(s->streams[0], wc->pos, pkt->pts, 0, 0, AVINDEX_KEYFRAME);
    return 0;
}
