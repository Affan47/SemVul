brush_undo (splotd * sp, GGobiData * d, ggobid * gg)
{
  gint m, i;
  if (!d)
    return;

  g_assert (d->color.nels == d->nrows);

  for (m = 0; m < d->nrows_in_plot; m++) {
    i = d->rows_in_plot.els[m];
    d->color.els[i] = d->color_now.els[i] = d->color_prev.els[i];
    d->hidden.els[i] = d->hidden_now.els[i] = d->hidden_prev.els[i];
    d->glyph.els[i].type = d->glyph_now.els[i].type =
      d->glyph_prev.els[i].type;
    d->glyph.els[i].size = d->glyph_now.els[i].size =
      d->glyph_prev.els[i].size;
  }
}
