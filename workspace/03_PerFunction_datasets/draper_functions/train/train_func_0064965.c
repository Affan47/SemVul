handle_owners_changed_prepared_cb (GObject *object,
    GAsyncResult *result,
    gpointer user_data)
{
  TpChannel *self = (TpChannel *) object;
  HandleOwnersChangedData *data = user_data;
  guint i;

  _tp_channel_contacts_queue_prepare_finish (self, result, NULL, NULL);

  for (i = 0; i < data->removed->len; i++)
    {
      g_hash_table_remove (self->priv->group_contact_owners,
          GUINT_TO_POINTER (g_array_index (data->removed, TpHandle, i)));
    }

  tp_g_hash_table_update (self->priv->group_contact_owners, data->added, NULL,
      safe_g_object_ref);

  handle_owners_changed_data_free (data);
}
