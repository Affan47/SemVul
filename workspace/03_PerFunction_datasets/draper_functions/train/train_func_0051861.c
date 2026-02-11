setFilter(char** filter, int nfilter)
{
	int i;

	if (_filter)
	{
    for (i = 0; i < (int)_filter->len; i++)
      g_free(g_ptr_array_index(_filter, i));

    g_ptr_array_free(_filter, true);
    _filter = NULL;
  }

  if (!filter)
    return;

	_filter = g_ptr_array_new();
  for (i = 0; i < nfilter; i++)
    g_ptr_array_add(_filter, (gpointer)g_strdup(filter[i]));
}
