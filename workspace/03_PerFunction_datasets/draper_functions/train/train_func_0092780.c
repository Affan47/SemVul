varlist_populate (GtkListStore * list, GGobiData * d)
{
  gint j;
  GtkTreeIter first;
  vartabled *vt;

  gtk_list_store_append (list, &first);
  gtk_list_store_set (list, &first, LINKBYLIST_NAME, "<i>Case ID</i>", -1);

  for (j = 0; j < d->ncols; j++) {
    vt = vartable_element_get (j, d);
    varlist_append (list, vt);
  }
}
