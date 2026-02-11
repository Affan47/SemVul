img_read_header(AVFormatContext *s1, AVFormatParameters *ap)
{
    VideoData *s = s1->priv_data;
    int first_index, last_index;
    AVStream *st;

    s1->ctx_flags |= AVFMTCTX_NOHEADER;

    st = av_new_stream(s1, 0);
    if (!st) {
        return AVERROR(ENOMEM);
    }

    av_strlcpy(s->path, s1->filename, sizeof(s->path));
    s->img_number = 0;
    s->img_count = 0;


    if (s1->iformat->flags & AVFMT_NOFILE)
        s->is_pipe = 0;
    else{
        s->is_pipe = 1;
        st->need_parsing = AVSTREAM_PARSE_FULL;
    }

    if (!ap->time_base.num) {
        av_set_pts_info(st, 60, 1, 25);
    } else {
        av_set_pts_info(st, 60, ap->time_base.num, ap->time_base.den);
    }

    if(ap->width && ap->height){
        st->codec->width = ap->width;
        st->codec->height= ap->height;
    }

    if (!s->is_pipe) {
        if (find_image_range(&first_index, &last_index, s->path) < 0)
            return AVERROR(EIO);
        s->img_first = first_index;
        s->img_last = last_index;
        s->img_number = first_index;

        st->start_time = 0;
        st->duration = last_index - first_index + 1;
    }

    if(ap->video_codec_id){
        st->codec->codec_type = CODEC_TYPE_VIDEO;
        st->codec->codec_id = ap->video_codec_id;
    }else if(ap->audio_codec_id){
        st->codec->codec_type = CODEC_TYPE_AUDIO;
        st->codec->codec_id = ap->audio_codec_id;
    }else{
        st->codec->codec_type = CODEC_TYPE_VIDEO;
        st->codec->codec_id = av_str2id(img_tags, s->path);
    }
    if(st->codec->codec_type == CODEC_TYPE_VIDEO && ap->pix_fmt != PIX_FMT_NONE)
        st->codec->pix_fmt = ap->pix_fmt;

    return 0;
}
