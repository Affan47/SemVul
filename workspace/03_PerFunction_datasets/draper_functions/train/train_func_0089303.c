test_gradient (void)
{
  ArtVpath *vpath;
  ArtSVP *svp;
  art_u8 buf[512 * 512 * 3];
  ArtRender *render;
  ArtPixMaxDepth color[3] = {0x0000, 0x0000, 0x8000 };
  int i;
  const int n_iter = 1;

  vpath = randstar (50);
  svp = art_svp_from_vpath (vpath);

  for (i = 0; i < n_iter; i++)
    {
#define USE_RENDER
#ifdef USE_RENDER
      render = art_render_new (0, 0, 512, 512, buf, 512 * 3, 3, 8, ART_ALPHA_NONE,
			       NULL);
      art_render_clear_rgb (render, 0xfff0c0);
      art_render_svp (render, svp);
      art_render_image_solid (render, color);
      art_render_invoke (render);
#else
      art_rgb_svp_aa (svp, 0, 0, 512, 512, 0xfff0c0, 0x000080,
		      buf, 512 * 3, NULL);
#endif
    }

#if 1
  test_render_gradient (buf);
#endif
  test_render_rad_gradient (buf);

  printf ("P6\n512 512\n255\n");
  fwrite (buf, 1, 512 * 512 * 3, stdout);
}
