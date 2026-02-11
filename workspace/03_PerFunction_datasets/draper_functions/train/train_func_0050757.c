av_set_parameters(AVFormatContext *s, AVFormatParameters *ap)
{
    int ret;

    if (s->oformat->priv_data_size > 0) {
        s->priv_data = av_mallocz(s->oformat->priv_data_size);
        if (!s->priv_data)
            return AVERROR(ENOMEM);
    } else
        s->priv_data = NULL;

    if (s->oformat->set_parameters) {
        ret = s->oformat->set_parameters(s, ap);
        if (ret < 0)
            return ret;
    }
    return 0;
}
