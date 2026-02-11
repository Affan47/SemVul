shader_fade_and_move_horiz_in (GstAudioVisualizer * scope,
    const GstVideoFrame * sframe, GstVideoFrame * dframe)
{
  guint i, j;
  guint r = (scope->shade_amount >> 16) & 0xff;
  guint g = (scope->shade_amount >> 8) & 0xff;
  guint b = (scope->shade_amount >> 0) & 0xff;
  guint8 *s, *d;
  gint ss, ds, width, height;

  s = GST_VIDEO_FRAME_PLANE_DATA (sframe, 0);
  ss = GST_VIDEO_FRAME_PLANE_STRIDE (sframe, 0);
  d = GST_VIDEO_FRAME_PLANE_DATA (dframe, 0);
  ds = GST_VIDEO_FRAME_PLANE_STRIDE (dframe, 0);

  width = GST_VIDEO_FRAME_WIDTH (sframe);
  height = GST_VIDEO_FRAME_HEIGHT (sframe);


  for (j = 0; j < height / 2; j++) {
    d += ds;
    for (i = 0; i < width; i++) {
      SHADE (d, s, i, r, g, b);
    }
    s += ss;
  }

  for (j = 0; j < height / 2; j++) {
    s += ss;
    for (i = 0; i < width; i++) {
      SHADE (d, s, i, r, g, b);
    }
    d += ds;
  }
}
