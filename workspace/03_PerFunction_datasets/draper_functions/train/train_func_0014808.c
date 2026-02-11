read_header(AVFormatContext *s,
                           AVFormatParameters *ap)
{
    AVStream *video;
    ByteIOContext *pb = s->pb;
    C93DemuxContext *c93 = s->priv_data;
    int i;
    int framecount = 0;

    for (i = 0; i < 512; i++) {
        c93->block_records[i].index = get_le16(pb);
        c93->block_records[i].length = get_byte(pb);
        c93->block_records[i].frames = get_byte(pb);
        if (c93->block_records[i].frames > 32) {
            av_log(s, AV_LOG_ERROR, "too many frames in block\n");
            return AVERROR_INVALIDDATA;
        }
        framecount += c93->block_records[i].frames;
    }


    s->ctx_flags |= AVFMTCTX_NOHEADER;

    video = av_new_stream(s, 0);
    if (!video)
        return AVERROR(ENOMEM);

    video->codec->codec_type = CODEC_TYPE_VIDEO;
    video->codec->codec_id = CODEC_ID_C93;
    video->codec->width = 320;
    video->codec->height = 192;

    video->sample_aspect_ratio = (AVRational) { 5, 6 };
    video->time_base = (AVRational) { 2, 25 };
    video->nb_frames = framecount;
    video->duration = framecount;
    video->start_time = 0;

    c93->current_block = 0;
    c93->current_frame = 0;
    c93->next_pkt_is_audio = 0;
    return 0;
}
