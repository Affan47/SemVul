wav_read_seek(AVFormatContext *s,
                         int stream_index, int64_t timestamp, int flags)
{
    AVStream *st;

    st = s->streams[0];
    switch(st->codec->codec_id) {
    case CODEC_ID_MP2:
    case CODEC_ID_MP3:
    case CODEC_ID_AC3:
    case CODEC_ID_DTS:

        return -1;
    default:
        break;
    }
    return pcm_read_seek(s, stream_index, timestamp, flags);
}
