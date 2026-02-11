print_keys (const GList *keys)
{
  GList *k;
  GList *sorted = NULL;

  if (!keys) {
    g_print ("---");
    return;
  }


  for (k = (GList *) keys;
       k;
       k = g_list_next (k)) {
    sorted = g_list_insert_sorted (sorted, k->data, (GCompareFunc) compare_keys);
  }

  k = sorted;
  while (k) {
    g_print ("%s",
             GRL_METADATA_KEY_GET_NAME (GRLPOINTER_TO_KEYID (k->data)));
    k = g_list_next (k);
    if (k) {
      g_print (", ");
    }
  }

  g_list_free (sorted);
}
