dvdsub_decode(AVCodecContext *avctx,
                         void *data, int *data_size,
                         const uint8_t *buf, int buf_size)
{
    AVSubtitle *sub = (void *)data;
    int is_menu;

    is_menu = decode_dvd_subtitles(sub, buf, buf_size);

    if (is_menu < 0) {
    no_subtitle:
        *data_size = 0;

        return buf_size;
    }
    if (!is_menu && find_smallest_bounding_rectangle(sub) == 0)
        goto no_subtitle;

#if defined(DEBUG)
    av_log(NULL, AV_LOG_INFO, "start=%d ms end =%d ms\n",
           sub->start_display_time,
           sub->end_display_time);
    ppm_save("/tmp/a.ppm", sub->rects[0]->pict.data[0],
             sub->rects[0]->w, sub->rects[0]->h, sub->rects[0]->pict.data[1]);
#endif

    *data_size = 1;
    return buf_size;
}
