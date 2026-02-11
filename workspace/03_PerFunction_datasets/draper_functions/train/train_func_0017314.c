r3d_read_red1(AVFormatContext *s)
{
    AVStream *st = av_new_stream(s, 0);
    char filename[258];
    int tmp, tmp2;

    if (!st)
        return -1;
    st->codec->codec_type = CODEC_TYPE_VIDEO;
    st->codec->codec_id = CODEC_ID_JPEG2000;

    tmp  = get_byte(s->pb);
    tmp2 = get_byte(s->pb);
    dprintf(s, "version %d.%d\n", tmp, tmp2);

    tmp = get_be16(s->pb);
    dprintf(s, "unknown1 %d\n", tmp);

    tmp = get_be32(s->pb);
    av_set_pts_info(st, 32, 1, tmp);

    tmp = get_be32(s->pb);
    dprintf(s, "filenum %d\n", tmp);

    url_fskip(s->pb, 32);

    st->codec->width  = get_be32(s->pb);
    st->codec->height = get_be32(s->pb);

    tmp = get_be16(s->pb);
    dprintf(s, "unknown2 %d\n", tmp);

    st->codec->time_base.den = get_be16(s->pb);
    st->codec->time_base.num = get_be16(s->pb);

    tmp = get_byte(s->pb);
    dprintf(s, "audio channels %d\n", tmp);
    if (tmp > 0) {
        AVStream *ast = av_new_stream(s, 1);
        ast->codec->codec_type = CODEC_TYPE_AUDIO;
        ast->codec->codec_id = CODEC_ID_PCM_S32BE;
        ast->codec->channels = tmp;
        av_set_pts_info(ast, 32, 1, st->time_base.den);
    }

    get_buffer(s->pb, filename, 257);
    filename[sizeof(filename)-1] = 0;
    av_metadata_set(&st->metadata, "filename", filename);

    dprintf(s, "filename %s\n", filename);
    dprintf(s, "resolution %dx%d\n", st->codec->width, st->codec->height);
    dprintf(s, "timescale %d\n", st->time_base.den);
    dprintf(s, "frame rate %d/%d\n",
            st->codec->time_base.num, st->codec->time_base.den);

    return 0;
}
