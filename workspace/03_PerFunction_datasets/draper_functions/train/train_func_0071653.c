pixbuf_scale(unsigned char *source,
                  int source_rowstride,
                  int source_width,
                  int source_height,
                  unsigned char *dest,
                  int dest_rowstride,
                  int dest_width,
                  int dest_height,
                  bool alpha)
{
    if (alpha) {
        YScaler<Pixel, 4>(source, source_rowstride, source_width, source_height,
                          dest, dest_rowstride, dest_width, dest_height);
    } else {
        YScaler<Pixel, 3>(source, source_rowstride, source_width, source_height,
                          dest, dest_rowstride, dest_width, dest_height);
    }
}
