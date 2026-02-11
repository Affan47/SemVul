art_render_clear_rgb (ArtRender *render, art_u32 clear_rgb)
{
  if (render->n_chan != 3)
    art_warn ("art_render_clear_rgb: called on render with %d channels, only works with 3\n",
	      render->n_chan);
  else
    {
      int r, g, b;

      render->clear = ART_TRUE;
      r = clear_rgb >> 16;
      g = (clear_rgb >> 8) & 0xff;
      b = clear_rgb & 0xff;
      render->clear_color[0] = ART_PIX_MAX_FROM_8(r);
      render->clear_color[1] = ART_PIX_MAX_FROM_8(g);
      render->clear_color[2] = ART_PIX_MAX_FROM_8(b);
    }
}
