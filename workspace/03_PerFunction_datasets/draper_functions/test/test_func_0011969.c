open_parser(AVFormatContext *s, int i)
{
    AVStream *st = s->streams[i];
    AVCodec *codec;

    if (!st->codec->codec) {
        codec = avcodec_find_decoder(st->codec->codec_id);
        if (codec && (codec->capabilities & CODEC_CAP_PARSE_ONLY)) {
            st->codec->parse_only = 1;
            if (avcodec_open(st->codec, codec) < 0)
                st->codec->parse_only = 0;
        }
    }
}
