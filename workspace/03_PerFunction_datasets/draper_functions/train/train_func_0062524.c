barchart_init_categorical (barchartSPlotd * sp, GGobiData * d)
{
  splotd *rawsp = GGOBI_SPLOT (sp);
  displayd *display = (displayd *) rawsp->displayptr;
  gint proj = display->cpanel.pmode;
  gint i, j, m, jvar = rawsp->p1dvar;
  ggobid *gg = GGobiFromSPlot (rawsp);
  vartabled *vtx = vartable_element_get (rawsp->p1dvar, d);
  gfloat mindist, maxheight;
  gfloat min, max;

  gfloat *yy;
  yy = (gfloat *) g_malloc (d->nrows_in_plot * sizeof (gfloat));

  if (proj == TOUR1D) {
    for (m=0; m < d->nrows_in_plot; m++) {
      i = d->rows_in_plot.els[m];
      yy[m] = rawsp->planar[i].x = 0;
      rawsp->planar[i].y = 0;
      for (j=0; j<d->ncols; j++)
      {
        yy[m] += (gfloat)(display->t1d.F.vals[0][j]*d->world.vals[i][j]);
      }
    }
  }
  else {
    for (i = 0; i < d->nrows_in_plot; i++)
      yy[i] = d->tform.vals[d->rows_in_plot.els[i]][jvar];
  }
  mindist = barchart_sort_index (yy, d->nrows_in_plot, gg, sp);
  g_free ((gpointer) yy);

  min = vtx->lim_tform.min;
  max = vtx->lim_tform.max;

  if (vtx->vartype == categorical) {
    min = MIN (min, vtx->level_values[0]);
    max = MAX (max, vtx->level_values[vtx->nlevels - 1]);
  }


  maxheight = max - min;

  rawsp->scale.y =
    (1 - (1.0 - SCALE_DEFAULT) / 2) * maxheight / (maxheight + mindist);
}
