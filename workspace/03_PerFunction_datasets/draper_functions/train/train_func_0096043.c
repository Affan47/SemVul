pw_list_entries(Vfs_handle *h)
{
  int n;
  Dsvec *dsv;

  dsv = dsvec_init(NULL, sizeof(char *));
  h->list_sort = list_qsort;
  if ((n = vfs_list(h, NULL, list_compar, list_add, (void ***) dsv)) == -1)
	return(NULL);

  return(dsv);
}
