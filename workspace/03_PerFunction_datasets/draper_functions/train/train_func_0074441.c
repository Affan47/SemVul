write_csv_records (gint *cols, gint ncols, FILE *f, GGobiData *d, ggobid *gg)
{
  gboolean ok = true;
  gint i, m;

  if (gg->save.row_ind == ALLROWS) {
    for (i = 0; i < d->nrows; i++) {
      write_csv_record (i, cols, ncols, f, d, gg);
      fprintf(f, "\n");
    }
  } else {
    for (i=0; i<d->nrows_in_plot; i++) {
      m = d->rows_in_plot.els[i];
      write_csv_record (m, cols, ncols, f, d, gg);
      fprintf(f, "\n");
    }
  }

  return ok;
}
