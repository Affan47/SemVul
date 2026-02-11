encode_strip(TiffEncoderContext * s, const int8_t * src,
                        uint8_t * dst, int n, int compr)
{

    switch (compr) {
#if CONFIG_ZLIB
    case TIFF_DEFLATE:
    case TIFF_ADOBE_DEFLATE:
        {
            unsigned long zlen = s->buf_size - (*s->buf - s->buf_start);
            if (compress(dst, &zlen, src, n) != Z_OK) {
                av_log(s->avctx, AV_LOG_ERROR, "Compressing failed\n");
                return -1;
            }
            return zlen;
        }
#endif
    case TIFF_RAW:
        if (check_size(s, n))
            return -1;
        memcpy(dst, src, n);
        return n;
    case TIFF_PACKBITS:
        return ff_rle_encode(dst, s->buf_size - (*s->buf - s->buf_start), src, 1, n, 2, 0xff, -1, 0);
    case TIFF_LZW:
        return ff_lzw_encode(s->lzws, src, n);
    default:
        return -1;
    }
}
