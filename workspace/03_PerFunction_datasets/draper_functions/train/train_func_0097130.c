convert_no_alpha (guchar *dest_data,
                  int     dest_stride,
                  guchar *src_data,
                  int     src_stride,
                  int     src_x,
                  int     src_y,
                  int     width,
                  int     height)
{
    int x, y;

    src_data += src_stride * src_y + src_x * 4;

    for (y = 0; y < height; y++) {
        guint32 *src = (guint32 *) src_data;

        for (x = 0; x < width; x++) {
            dest_data[x * 3 + 0] = src[x] >> 16;
            dest_data[x * 3 + 1] = src[x] >>  8;
            dest_data[x * 3 + 2] = src[x];
        }

        src_data += src_stride;
        dest_data += dest_stride;
    }
}
