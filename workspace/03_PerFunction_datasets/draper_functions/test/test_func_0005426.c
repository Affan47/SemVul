dummy_encode_ctx (void)
{
  th_enc_ctx *ctx;
  th_info info;


  th_info_init (&info);
  info.frame_width = 320;
  info.frame_height = 240;
  info.fps_numerator = 1;
  info.fps_denominator = 1;


  ctx = th_encode_alloc (&info);
  if (!ctx)
    GST_WARNING ("Failed to allocate dummy encoder context.");


  th_info_clear (&info);

  return ctx;
}
