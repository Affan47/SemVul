theora_enc_get_supported_formats (void)
{
  th_enc_ctx *encoder;
  th_info info;
  static const struct
  {
    th_pixel_fmt pixelformat;
    const char fourcc[5];
  } formats[] = {
    {
    TH_PF_420, "I420"}, {
    TH_PF_422, "Y42B"}, {
    TH_PF_444, "Y444"}
  };
  GString *string = NULL;
  guint i;

  th_info_init (&info);
  info.frame_width = 16;
  info.frame_height = 16;
  info.fps_numerator = 25;
  info.fps_denominator = 1;
  for (i = 0; i < G_N_ELEMENTS (formats); i++) {
    info.pixel_fmt = formats[i].pixelformat;

    encoder = th_encode_alloc (&info);
    if (encoder == NULL)
      continue;

    GST_LOG ("format %s is supported", formats[i].fourcc);
    th_encode_free (encoder);

    if (string == NULL) {
      string = g_string_new (formats[i].fourcc);
    } else {
      g_string_append (string, ", ");
      g_string_append (string, formats[i].fourcc);
    }
  }
  th_info_clear (&info);

  return string == NULL ? NULL : g_string_free (string, FALSE);
}
