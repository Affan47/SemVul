tp_capabilities_supports_contact_search (TpCapabilities *self,
    gboolean *with_limit,
    gboolean *with_server)
{
  gboolean ret = FALSE;
  guint i, j;

  g_return_val_if_fail (TP_IS_CAPABILITIES (self), FALSE);

  if (with_limit)
    *with_limit = FALSE;

  if (with_server)
    *with_server = FALSE;

  for (i = 0; i < self->priv->classes->len; i++)
    {
      GValueArray *arr = g_ptr_array_index (self->priv->classes, i);
      GHashTable *fixed;
      const gchar *chan_type;
      const gchar **allowed_properties;

      tp_value_array_unpack (arr, 2, &fixed, &allowed_properties);


      if (g_hash_table_size (fixed) != 1)
        continue;

      chan_type = tp_asv_get_string (fixed, TP_PROP_CHANNEL_CHANNEL_TYPE);
      if (tp_strdiff (chan_type, TP_IFACE_CHANNEL_TYPE_CONTACT_SEARCH))
        continue;

      ret = TRUE;

      for (j = 0; allowed_properties[j] != NULL; j++)
        {
          if (with_limit)
            {
              if (!tp_strdiff (allowed_properties[j],
                       TP_PROP_CHANNEL_TYPE_CONTACT_SEARCH_LIMIT))
                *with_limit = TRUE;
            }

          if (with_server)
            {
              if (!tp_strdiff (allowed_properties[j],
                       TP_PROP_CHANNEL_TYPE_CONTACT_SEARCH_SERVER))
                *with_server = TRUE;
            }
        }
    }

  return ret;
}
