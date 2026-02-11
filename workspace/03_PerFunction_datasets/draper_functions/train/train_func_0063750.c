av_picture_crop(AVPicture *dst, const AVPicture *src,
              int pix_fmt, int top_band, int left_band)
{
    int y_shift;
    int x_shift;

    if (pix_fmt < 0 || pix_fmt >= PIX_FMT_NB || !is_yuv_planar(&pix_fmt_info[pix_fmt]))
        return -1;

    y_shift = pix_fmt_info[pix_fmt].y_chroma_shift;
    x_shift = pix_fmt_info[pix_fmt].x_chroma_shift;

    dst->data[0] = src->data[0] + (top_band * src->linesize[0]) + left_band;
    dst->data[1] = src->data[1] + ((top_band >> y_shift) * src->linesize[1]) + (left_band >> x_shift);
    dst->data[2] = src->data[2] + ((top_band >> y_shift) * src->linesize[2]) + (left_band >> x_shift);

    dst->linesize[0] = src->linesize[0];
    dst->linesize[1] = src->linesize[1];
    dst->linesize[2] = src->linesize[2];
    return 0;
}
