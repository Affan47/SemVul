ggv_init_Dtarget (gint selected_var, ggvisd *ggv)
{
  gint i, j;
  gdouble infinity, largest = -1;
  GGobiData *e = ggv->e;
  gint indx = -1;


  infinity = (gdouble) (2 * ggv->Dtarget.nrows);
  if (selected_var >= 0 && selected_var < e->tform.ncols) {
    largest = e->tform.vals[0][selected_var];
    for (i=0; i<e->edge.n; i++) {
      if (e->tform.vals[i][selected_var] > infinity) {
        infinity = e->tform.vals[i][selected_var];
        indx = i;
      }
      if (e->tform.vals[i][selected_var] > largest) {
        largest = e->tform.vals[i][selected_var];
      }
    }
  }


  if (largest != -1) {
    g_printerr ("largest dissimilarity: %.3f\n", largest);
    if (largest > 100000) {
      gchar *stmp = g_strdup_printf ("Warning: your largest weight, %.2f (index %d), is extremely large. ", largest, indx);
      quick_message (stmp, false);
      g_free (stmp);
    }
  }


  for (i=0; i<ggv->Dtarget.nrows; i++) {
    for (j=0; j<ggv->Dtarget.ncols; j++)
      ggv->Dtarget.vals[i][j] = infinity;
    ggv->Dtarget.vals[i][i] = 0.0;
  }
}
