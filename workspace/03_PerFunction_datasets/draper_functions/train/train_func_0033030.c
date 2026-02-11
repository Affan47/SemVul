art_rgb_svp_alpha (const ArtSVP *svp,
		   int x0, int y0, int x1, int y1,
		   art_u32 rgba,
		   art_u8 *buf, int rowstride,
		   ArtAlphaGamma *alphagamma)
{
  ArtRgbSVPAlphaData data;
  int r, g, b, alpha;
  int i;
  int a, da;

  r = rgba >> 24;
  g = (rgba >> 16) & 0xff;
  b = (rgba >> 8) & 0xff;
  alpha = rgba & 0xff;

  data.r = r;
  data.g = g;
  data.b = b;
  data.alpha = alpha;

  a = 0x8000;
  da = (alpha * 66051 + 0x80) >> 8;

  for (i = 0; i < 256; i++)
    {
      data.alphatab[i] = a >> 16;
      a += da;
    }

  data.buf = buf;
  data.rowstride = rowstride;
  data.x0 = x0;
  data.x1 = x1;
  if (alpha == 255)
    art_svp_render_aa (svp, x0, y0, x1, y1, art_rgb_svp_alpha_opaque_callback,
		       &data);
  else
    art_svp_render_aa (svp, x0, y0, x1, y1, art_rgb_svp_alpha_callback, &data);
}
