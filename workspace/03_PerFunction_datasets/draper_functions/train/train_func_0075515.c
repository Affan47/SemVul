gst_video_test_src_gamut (GstVideoTestSrc * v, guchar * dest, int w, int h)
{
  int x, y;
  paintinfo pi = { NULL, };
  paintinfo *p = &pi;
  struct fourcc_list_struct *fourcc;
  struct vts_color_struct yuv_primary;
  struct vts_color_struct yuv_secondary;

  videotestsrc_setup_paintinfo (v, p, w, h);
  fourcc = v->fourcc;
  if (fourcc == NULL)
    return;

  fourcc->paint_setup (p, dest);

  for (y = 0; y < h; y++) {
    int region = (y * 4) / h;

    switch (region) {
      case 0:
        yuv_primary = p->colors[COLOR_BLACK];
        yuv_secondary = p->colors[COLOR_BLACK];
        yuv_secondary.Y = 0;
        break;
      case 1:
        yuv_primary = p->colors[COLOR_WHITE];
        yuv_secondary = p->colors[COLOR_WHITE];
        yuv_secondary.Y = 255;
        break;
      case 2:
        yuv_primary = p->colors[COLOR_RED];
        yuv_secondary = p->colors[COLOR_RED];
        yuv_secondary.V = 255;
        break;
      case 3:
        yuv_primary = p->colors[COLOR_BLUE];
        yuv_secondary = p->colors[COLOR_BLUE];
        yuv_secondary.U = 255;
        break;
    }

    for (x = 0; x < w; x += 8) {
      int len = MIN (8, w - x);

      if ((x ^ y) & (1 << 4)) {
        p->color = &yuv_primary;
      } else {
        p->color = &yuv_secondary;
      }
      p->paint_tmpline (p, x, len);
    }
    videotestsrc_convert_tmpline (p, y);
  }
}
