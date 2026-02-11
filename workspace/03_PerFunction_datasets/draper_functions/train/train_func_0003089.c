render_dots (GstAudioVisualizer * base, guint32 * vdata, gint16 * adata,
    guint num_samples)
{
  gint channels = GST_AUDIO_INFO_CHANNELS (&base->ainfo);
  guint i, c, s, x, y, oy;
  gfloat dx, dy;
  guint w = GST_VIDEO_INFO_WIDTH (&base->vinfo);
  guint h = GST_VIDEO_INFO_HEIGHT (&base->vinfo);


  dx = (gfloat) w / (gfloat) num_samples;
  dy = h / 65536.0;
  oy = h / 2;
  for (c = 0; c < channels; c++) {
    s = c;
    for (i = 0; i < num_samples; i++) {
      x = (guint) ((gfloat) i * dx);
      y = (guint) (oy + (gfloat) adata[s] * dy);
      s += channels;
      draw_dot (vdata, x, y, w, 0x00FFFFFF);
    }
  }
}
