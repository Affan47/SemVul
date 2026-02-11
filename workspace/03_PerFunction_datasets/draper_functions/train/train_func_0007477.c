record_colors_reset (gint selected_var, GGobiData *d, ggobid *gg)
{
  gint i, k, m;
  gint nd = g_slist_length(gg->d);
  vartabled *vt;
  gfloat min, max, val;
  colorschemed *scheme = gg->activeColorScheme;

  if (selected_var < 0)
    return;

  vt = vartable_element_get (selected_var, d);
  min = vt->lim_tform.min;
  max = vt->lim_tform.max;

  for (m=0; m<d->nrows_in_plot; m++) {
    i = d->rows_in_plot.els[m];
    for (k=0; k<scheme->n; k++) {
      val = min + gg->wvis.pct[k] * (max - min);
      if (d->tform.vals[i][selected_var] <= val) {
        d->color.els[i] = d->color_now.els[i] = k;
        break;
      }
    }
    if (nd > 1 && !gg->linkby_cv)
      symbol_link_by_id (true, i, d, gg);
  }
}
