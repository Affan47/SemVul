_tp_cm_message_new_from_parts (TpBaseConnection *conn,
    const GPtrArray *parts)
{
  TpMessage *self;
  guint i;
  const GHashTable *header;
  TpHandle sender;

  g_return_val_if_fail (parts != NULL, NULL);
  g_return_val_if_fail (parts->len > 0, NULL);

  self = tp_cm_message_new (conn, parts->len);

  for (i = 0; i < parts->len; i++)
    {
      tp_g_hash_table_update (g_ptr_array_index (self->parts, i),
          g_ptr_array_index (parts, i),
          (GBoxedCopyFunc) g_strdup,
          (GBoxedCopyFunc) tp_g_value_slice_dup);
    }

  header = tp_message_peek (self, 0);
  sender = tp_asv_get_uint32 (header, "message-sender", NULL);
  if (sender != 0)
    tp_cm_message_set_sender (self, sender);

  return self;
}
