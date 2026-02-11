ogg_write_header(AVFormatContext *s)
{
    OGGStreamContext *oggstream;
    int i, j;
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        if (st->codec->codec_type == CODEC_TYPE_AUDIO)
            av_set_pts_info(st, 64, 1, st->codec->sample_rate);
        else if (st->codec->codec_type == CODEC_TYPE_VIDEO)
            av_set_pts_info(st, 64, st->codec->time_base.num, st->codec->time_base.den);
        if (st->codec->codec_id != CODEC_ID_VORBIS &&
            st->codec->codec_id != CODEC_ID_THEORA &&
            st->codec->codec_id != CODEC_ID_FLAC) {
            av_log(s, AV_LOG_ERROR, "Unsupported codec id in stream %d\n", i);
            return -1;
        }

        if (!st->codec->extradata || !st->codec->extradata_size) {
            av_log(s, AV_LOG_ERROR, "No extradata present\n");
            return -1;
        }
        oggstream = av_mallocz(sizeof(*oggstream));
        st->priv_data = oggstream;
        if (st->codec->codec_id == CODEC_ID_FLAC) {
            if (ogg_build_flac_headers(st->codec,
                                       oggstream, st->codec->flags & CODEC_FLAG_BITEXACT) < 0) {
                av_log(s, AV_LOG_ERROR, "Extradata corrupted\n");
                av_freep(&st->priv_data);
            }
        } else {
            if (ff_split_xiph_headers(st->codec->extradata, st->codec->extradata_size,
                                      st->codec->codec_id == CODEC_ID_VORBIS ? 30 : 42,
                                      oggstream->header, oggstream->header_len) < 0) {
                av_log(s, AV_LOG_ERROR, "Extradata corrupted\n");
                av_freep(&st->priv_data);
                return -1;
            }
            if (st->codec->codec_id == CODEC_ID_THEORA) {


                oggstream->kfgshift = ((oggstream->header[0][40]&3)<<3)|(oggstream->header[0][41]>>5);
                oggstream->vrev = oggstream->header[0][9];
                av_log(s, AV_LOG_DEBUG, "theora kfgshift %d, vrev %d\n",
                       oggstream->kfgshift, oggstream->vrev);
            }
        }
    }
    for (i = 0; i < 3; i++) {
        for (j = 0; j < s->nb_streams; j++) {
            AVStream *st = s->streams[j];
            OGGStreamContext *oggstream = st->priv_data;
            if (oggstream && oggstream->header_len[i]) {
                ogg_write_page(s, oggstream->header[i], oggstream->header_len[i],
                               0, st->index, i ? 0 : 2);
            }
        }
    }
    return 0;
}
