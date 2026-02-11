realloc_optimize0_p (optimize0_param *op, gint ncols, vector_i pcols)
{
  gint i, ncolsdel;
  gint *cols;


  if (op->proj_best.ncols < ncols) {
    arrayf_add_cols(&op->proj_best, ncols);
    arrayf_add_cols(&op->data, ncols);
  }
  else {
    ncolsdel = op->proj_best.ncols - ncols;
    cols = g_malloc (ncolsdel*sizeof(gint));
    for (i=0; i<ncolsdel; i++)
      cols[i] = ncols-1-i;

    arrayf_delete_cols(&op->proj_best, ncolsdel, cols);
    arrayf_delete_cols(&op->data, ncolsdel, cols);
    g_free (cols);
  }

  return 0;
}
