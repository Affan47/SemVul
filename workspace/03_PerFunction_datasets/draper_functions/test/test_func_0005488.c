pseudo_list(Vfs_handle *handle, int (*is_valid)(char *),
		int (*compar)(const void *, const void *),
		int (*add)(char *, char *, void ***), void ***names)
{
  int n;
  Kwv_iter *iter;
  Kwv_pair *pair;
  Handle *h;

  h = (Handle *) handle->h;

  if (load_and_parse(h) == -1)
	return(-1);

  n = 0;
  iter = kwv_iter_begin(h->kwv, NULL);
  while ((pair = kwv_iter_next(iter)) != NULL) {
	if (is_valid == NULL || is_valid(pair->name)) {
	  if (add(handle->sd->naming_context, pair->name, names) == 1)
		n++;
	}
  }
  kwv_iter_end(iter);

  if (compar != NULL) {
	if (handle->list_sort == NULL)
	  qsort(names, n, sizeof(void **), compar);
	else
	  handle->list_sort(names, n, sizeof(void **), compar);
  }

  return(n);
}
