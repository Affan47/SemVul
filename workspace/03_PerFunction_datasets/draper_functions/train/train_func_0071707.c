remove_elem_from_str_array (char **v,
                            const char *s)
{
  GPtrArray *array;
  guint idx;

  array = g_ptr_array_new ();

  for (idx = 0; v[idx] != NULL; idx++) {
    if (g_strcmp0 (v[idx], s) == 0) {
      continue;
    }

    g_ptr_array_add (array, v[idx]);
  }

  g_ptr_array_add (array, NULL);

  g_free (v);

  return (char **) g_ptr_array_free (array, FALSE);
}
