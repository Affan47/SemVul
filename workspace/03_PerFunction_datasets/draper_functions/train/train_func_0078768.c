avs_read_header(AVFormatContext * s, AVFormatParameters * ap)
{
    AvsFormat *avs = s->priv_data;

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    url_fskip(s->pb, 4);
    avs->width = get_le16(s->pb);
    avs->height = get_le16(s->pb);
    avs->bits_per_sample = get_le16(s->pb);
    avs->fps = get_le16(s->pb);
    avs->nb_frames = get_le32(s->pb);
    avs->remaining_frame_size = 0;
    avs->remaining_audio_size = 0;

    avs->st_video = avs->st_audio = NULL;

    if (avs->width != 318 || avs->height != 198)
        av_log(s, AV_LOG_ERROR, "This avs pretend to be %dx%d "
               "when the avs format is supposed to be 318x198 only.\n",
               avs->width, avs->height);

    return 0;
}
