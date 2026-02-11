example_contact_list_close_all (ExampleContactList *self)
{
  tp_clear_pointer (&self->priv->contacts, tp_handle_set_destroy);
  tp_clear_pointer (&self->priv->blocked_contacts, tp_handle_set_destroy);
  tp_clear_pointer (&self->priv->cancelled_publish_requests,
      tp_handle_set_destroy);
  tp_clear_pointer (&self->priv->publish_requests, g_hash_table_unref);
  tp_clear_pointer (&self->priv->contact_details, g_hash_table_unref);


  tp_clear_pointer (&self->priv->all_tags, g_hash_table_unref);

  if (self->priv->status_changed_id != 0)
    {
      g_signal_handler_disconnect (self->priv->conn,
          self->priv->status_changed_id);
      self->priv->status_changed_id = 0;
    }
}
