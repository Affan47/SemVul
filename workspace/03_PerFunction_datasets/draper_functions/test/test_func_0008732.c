convert_Y42B_I420 (VideoConvert * convert, GstVideoFrame * dest,
    const GstVideoFrame * src)
{
  gint width = convert->width;
  gint height = convert->height;

  video_convert_orc_memcpy_2d (FRAME_GET_Y_LINE (dest, 0),
      FRAME_GET_Y_STRIDE (dest), FRAME_GET_Y_LINE (src, 0),
      FRAME_GET_Y_STRIDE (src), width, height);

  video_convert_orc_planar_chroma_422_420 (FRAME_GET_U_LINE (dest, 0),
      FRAME_GET_U_STRIDE (dest), FRAME_GET_U_LINE (src, 0),
      2 * FRAME_GET_U_STRIDE (src), FRAME_GET_U_LINE (src, 1),
      2 * FRAME_GET_U_STRIDE (src), (width + 1) / 2, height / 2);

  video_convert_orc_planar_chroma_422_420 (FRAME_GET_V_LINE (dest, 0),
      FRAME_GET_V_STRIDE (dest), FRAME_GET_V_LINE (src, 0),
      2 * FRAME_GET_V_STRIDE (src), FRAME_GET_V_LINE (src, 1),
      2 * FRAME_GET_V_STRIDE (src), (width + 1) / 2, height / 2);


  if (height & 1) {
    UNPACK_FRAME (src, convert->tmplines[0], height - 1, width);
    PACK_FRAME (dest, convert->tmplines[0], height - 1, width);
  }
}
