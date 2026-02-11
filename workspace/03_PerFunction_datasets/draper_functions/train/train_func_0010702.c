set_codec_from_probe_data(AVStream *st, AVProbeData *pd, int score)
{
    AVInputFormat *fmt;
    fmt = av_probe_input_format2(pd, 1, &score);

    if (fmt) {
        if (!strcmp(fmt->name, "mp3")) {
            st->codec->codec_id = CODEC_ID_MP3;
            st->codec->codec_type = CODEC_TYPE_AUDIO;
        } else if (!strcmp(fmt->name, "ac3")) {
            st->codec->codec_id = CODEC_ID_AC3;
            st->codec->codec_type = CODEC_TYPE_AUDIO;
        } else if (!strcmp(fmt->name, "mpegvideo")) {
            st->codec->codec_id = CODEC_ID_MPEG2VIDEO;
            st->codec->codec_type = CODEC_TYPE_VIDEO;
        } else if (!strcmp(fmt->name, "m4v")) {
            st->codec->codec_id = CODEC_ID_MPEG4;
            st->codec->codec_type = CODEC_TYPE_VIDEO;
        } else if (!strcmp(fmt->name, "h264")) {
            st->codec->codec_id = CODEC_ID_H264;
            st->codec->codec_type = CODEC_TYPE_VIDEO;
        }
    }
    return !!fmt;
}
