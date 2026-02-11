thp_read_header(AVFormatContext *s,
                           AVFormatParameters *ap)
{
    ThpDemuxContext *thp = s->priv_data;
    AVStream *st;
    ByteIOContext *pb = s->pb;
    int i;


                           get_be32(pb);
    thp->version         = get_be32(pb);

                           get_be32(pb);
                           get_be32(pb);

    thp->fps             = av_d2q(av_int2flt(get_be32(pb)), INT_MAX);
    thp->framecnt        = get_be32(pb);
    thp->first_framesz   = get_be32(pb);
                           get_be32(pb);

    thp->compoff         = get_be32(pb);
                           get_be32(pb);
    thp->first_frame     = get_be32(pb);
    thp->last_frame      = get_be32(pb);

    thp->next_framesz    = thp->first_framesz;
    thp->next_frame      = thp->first_frame;


    url_fseek (pb, thp->compoff, SEEK_SET);
    thp->compcount       = get_be32(pb);


    get_buffer(pb, thp->components, 16);

    for (i = 0; i < thp->compcount; i++) {
        if (thp->components[i] == 0) {
            if (thp->vst != 0)
                break;


            st = av_new_stream(s, 0);
            if (!st)
                return AVERROR(ENOMEM);


            av_set_pts_info(st, 64, thp->fps.den, thp->fps.num);
            st->codec->codec_type = CODEC_TYPE_VIDEO;
            st->codec->codec_id = CODEC_ID_THP;
            st->codec->codec_tag = 0;
            st->codec->width = get_be32(pb);
            st->codec->height = get_be32(pb);
            st->codec->sample_rate = av_q2d(thp->fps);
            thp->vst = st;
            thp->video_stream_index = st->index;

            if (thp->version == 0x11000)
                get_be32(pb);
        } else if (thp->components[i] == 1) {
            if (thp->has_audio != 0)
                break;


            st = av_new_stream(s, 0);
            if (!st)
                return AVERROR(ENOMEM);

            st->codec->codec_type = CODEC_TYPE_AUDIO;
            st->codec->codec_id = CODEC_ID_ADPCM_THP;
            st->codec->codec_tag = 0;
            st->codec->channels    = get_be32(pb);
            st->codec->sample_rate = get_be32(pb);

            av_set_pts_info(st, 64, 1, st->codec->sample_rate);

            thp->audio_stream_index = st->index;
            thp->has_audio = 1;
        }
    }

    return 0;
}
