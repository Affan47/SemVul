decode_init(AVCodecContext *avctx){
    H264Context *h= avctx->priv_data;
    MpegEncContext * const s = &h->s;

    MPV_decode_defaults(s);

    s->avctx = avctx;
    common_init(h);

    s->out_format = FMT_H264;
    s->workaround_bugs= avctx->workaround_bugs;


    s->quarter_sample = 1;
    if(!avctx->has_b_frames)
    s->low_delay= 1;

    if(s->avctx->codec->capabilities&CODEC_CAP_HWACCEL_VDPAU)
        avctx->pix_fmt= PIX_FMT_VDPAU_H264;
    else
        avctx->pix_fmt= avctx->get_format(avctx, avctx->codec->pix_fmts);
    avctx->hwaccel = ff_find_hwaccel(avctx->codec->id, avctx->pix_fmt);

    decode_init_vlc();

    if(avctx->extradata_size > 0 && avctx->extradata &&
       *(char *)avctx->extradata == 1){
        h->is_avc = 1;
        h->got_avcC = 0;
    } else {
        h->is_avc = 0;
    }

    h->thread_context[0] = h;
    h->outputed_poc = INT_MIN;
    h->prev_poc_msb= 1<<16;
    reset_sei(h);
    if(avctx->codec_id == CODEC_ID_H264){
        if(avctx->ticks_per_frame == 1){
            s->avctx->time_base.den *=2;
        }
        avctx->ticks_per_frame = 2;
    }
    return 0;
}
