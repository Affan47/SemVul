update_call_members_prepared_cb (GObject *object,
    GAsyncResult *result,
    gpointer user_data)
{
  UpdateCallMembersData *data = user_data;
  TpCallChannel *self = data->self;
  GError *error = NULL;

  if (!_tp_channel_contacts_queue_prepare_finish ((TpChannel *) self,
      result, NULL, &error))
    {
      DEBUG ("Error preparing call members: %s", error->message);
      g_clear_error (&error);
    }

  tp_g_hash_table_update (self->priv->members, data->updates,
      g_object_ref, NULL);

  if (data->removed != NULL)
    {
      guint i;

      for (i = 0; i < data->removed->len; i++)
        {
          g_hash_table_remove (self->priv->members,
              g_ptr_array_index (data->removed, i));
        }
    }

  if (!self->priv->initial_members_retrieved)
    {
      self->priv->initial_members_retrieved = TRUE;

      channel_maybe_core_prepared (self);
    }
  else
    {
      g_signal_emit (self, _signals[MEMBERS_CHANGED], 0,
          data->updates, data->removed, data->reason);
    }

  tp_clear_pointer (&data->updates, g_hash_table_unref);
  tp_clear_pointer (&data->removed, g_ptr_array_unref);
  tp_clear_pointer (&data->reason, _tp_call_state_reason_unref);
  g_slice_free (UpdateCallMembersData, data);
}
