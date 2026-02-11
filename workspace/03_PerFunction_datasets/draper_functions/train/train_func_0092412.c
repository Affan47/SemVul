pipeline_arrays_alloc (GGobiData * d, ggobid * gg)
{
  gint nc = d->ncols, nr = d->nrows;

  if (d->tform.vals != NULL)
    pipeline_arrays_free (d, gg);

  arrayf_alloc (&d->tform, nr, nc);

  arrayg_alloc (&d->world, nr, nc);
  arrayg_alloc_zero (&d->jitdata, nr, nc);

  vectori_alloc (&d->rows_in_plot, nr);
  vectorb_alloc (&d->sampled, nr);
  vectorb_alloc (&d->excluded, nr);
}
