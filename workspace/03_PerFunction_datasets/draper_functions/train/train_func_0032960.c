vartable_element_get (gint j, GGobiData *d)
{
  vartabled *vt = (vartabled *) NULL;

  if (j < 0 || j >= d->ncols)
    g_printerr ("(vartable_element_get) illegal variable number %d\n", j);
  else
    vt = (vartabled *) g_slist_nth_data (d->vartable, j);

  return (vt);
}
