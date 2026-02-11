dvvideo_encode_frame(AVCodecContext *c, uint8_t *buf, int buf_size,
                                void *data)
{
    DVVideoContext *s = c->priv_data;

    s->sys = dv_codec_profile(c);
    if (!s->sys || buf_size < s->sys->frame_size || dv_init_dynamic_tables(s->sys))
        return -1;

    c->pix_fmt           = s->sys->pix_fmt;
    s->picture           = *((AVFrame *)data);
    s->picture.key_frame = 1;
    s->picture.pict_type = FF_I_TYPE;

    s->buf = buf;
    c->execute(c, dv_encode_video_segment, s->sys->work_chunks, NULL,
               dv_work_pool_size(s->sys), sizeof(DVwork_chunk));

    emms_c();

    dv_format_frame(s, buf);

    return s->sys->frame_size;
}
