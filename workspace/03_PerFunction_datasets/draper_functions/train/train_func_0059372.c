art_render_clear_render_16 (ArtRenderCallback *self, ArtRender *render,
			    art_u8 *dest, int y)
{
  int width = render->x1 - render->x0;
  int i, j;
  int n_ch = render->n_chan + (render->alpha_type != ART_ALPHA_NONE);
  int ix;
  art_u16 *dest_16 = (art_u16 *)dest;
  art_u8 color[ART_MAX_CHAN + 1];

  for (j = 0; j < n_ch; j++)
    {
      int color_16 = render->clear_color[j];
      color[j] = color_16;
    }

  ix = 0;
  for (i = 0; i < width; i++)
    for (j = 0; j < n_ch; j++)
      dest_16[ix++] = color[j];
}
