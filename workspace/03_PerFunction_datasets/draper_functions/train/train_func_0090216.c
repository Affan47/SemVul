grl_operation_options_set_key_filter_dictionary (GrlOperationOptions *options,
                                                 GHashTable *filters)
{
  GHashTableIter iter;
  gpointer _key, _value;
  gboolean ret = TRUE;

  g_hash_table_iter_init (&iter, filters);
  while (g_hash_table_iter_next (&iter, &_key, &_value)) {
    GrlKeyID key = GRLPOINTER_TO_KEYID (_key);
    GValue *value = (GValue *)_value;
    ret &=
        grl_operation_options_set_key_filter_value (options, key, value);
  }

  return ret;
}
