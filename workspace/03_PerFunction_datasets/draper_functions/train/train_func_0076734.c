arrays_alloc (array_s * arrp, gint nr, gint nc)
{
  int i;


  if (arrp->nrows != nr || arrp->ncols != nc) {

    if (arrp->nrows != 0 || arrp->ncols != 0)
      arrays_free (arrp, 0, 0);

    arrp->vals = (gshort **) g_malloc (nr * sizeof (gshort *));
    for (i = 0; i < nr; i++)
      arrp->vals[i] = (gshort *) g_malloc (nc * sizeof (gshort));
    arrp->nrows = nr;
    arrp->ncols = nc;
  }
}
