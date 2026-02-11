offer_finished_cb (GObject *source,
    GAsyncResult *result,
    gpointer user_data)
{
  TpBaseMediaCallContent *self = user_data;
  TpCallContentMediaDescription *md = (TpCallContentMediaDescription *) source;
  GHashTable *local_properties = NULL;
  GHashTable *remote_properties = NULL;
  TpHandle contact;
  GError *error = NULL;

  g_assert (self->priv->current_offer == md);

  if (!_tp_call_content_media_description_offer_finish (md, result,
          &local_properties, &error))
    {
      DEBUG ("Offer failed: %s", error->message);
      g_simple_async_result_take_error (self->priv->current_offer_result,
          error);
      goto out;
    }

  DEBUG ("Accepted offer: %s",
      tp_call_content_media_description_get_object_path (md));


  remote_properties = _tp_call_content_media_description_dup_properties (md);
  contact = tp_call_content_media_description_get_remote_contact (md);
  set_local_properties (self, contact, local_properties);
  set_remote_properties (self, contact, remote_properties);

out:
  g_simple_async_result_complete (self->priv->current_offer_result);
  g_clear_object (&self->priv->current_offer);
  g_clear_object (&self->priv->current_offer_result);
  g_clear_object (&self->priv->current_offer_cancellable);
  tp_svc_call_content_interface_media_emit_media_description_offer_done (self);

  next_offer (self);

  tp_clear_pointer (&local_properties, g_hash_table_unref);
  tp_clear_pointer (&remote_properties, g_hash_table_unref);
  g_object_unref (self);
}
