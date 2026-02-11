convert_UYVY_AYUV (ColorspaceConvert * convert, guint8 * dest,
    const guint8 * src)
{
  cogorc_convert_UYVY_AYUV (FRAME_GET_LINE (dest, 0, 0),
      convert->dest_stride[0], FRAME_GET_LINE (src, 0, 0),
      convert->src_stride[0], (convert->width + 1) / 2,
      convert->height & 1 ? convert->height - 1 : convert->height);


  if (convert->height & 1) {
    getline_UYVY (convert, convert->tmpline, src, convert->height - 1);
    putline_AYUV (convert, dest, convert->tmpline, convert->height - 1);
  }
}
