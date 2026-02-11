ggv_Dtarget_histogram_update (ggvisd *ggv, ggobid *gg)
{
  dissimd *D = ggv->dissim;
  GtkWidget *da = D->da;
  gint k;
  gint xmin = HISTOGRAM_HMARGIN;
  gint xmax = da->allocation.width - HISTOGRAM_HMARGIN;


  histogram_bins_reset (ggv);


  D->lgrip_pos = (gint) (D->low * (gdouble) (xmax - xmin) + (gdouble) xmin);
  D->rgrip_pos = (gint) (D->high * (gdouble) (xmax - xmin) + (gdouble) xmin);


  histogram_make (ggv);

  for (k=0; k<D->nbins; k++) {
    if (D->bars[k].x >= D->lgrip_pos &&
        D->bars[k].x + D->bars[k].width <= D->rgrip_pos) {
      D->bars_included.els[k] = true;
    } else {
      D->bars_included.els[k] = false;
    }
  }

  histogram_draw (ggv, gg);
}
