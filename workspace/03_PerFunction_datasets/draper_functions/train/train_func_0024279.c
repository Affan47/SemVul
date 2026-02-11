gray16_to_gray(AVPicture *dst, const AVPicture *src,
                              int width, int height)
{
    int x, y, src_wrap, dst_wrap;
    uint8_t *s, *d;
    s = src->data[0];
    src_wrap = src->linesize[0] - width * 2;
    d = dst->data[0];
    dst_wrap = dst->linesize[0] - width;
    for(y=0; y<height; y++){
        for(x=0; x<width; x++){
            *d++ = *s;
            s += 2;
        }
        s += src_wrap;
        d += dst_wrap;
    }
}
