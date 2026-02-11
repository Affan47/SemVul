daud_write_header(struct AVFormatContext *s)
{
    AVCodecContext *codec = s->streams[0]->codec;
    if (codec->channels!=6 || codec->sample_rate!=96000)
        return -1;
    return 0;
}
