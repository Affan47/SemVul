finalize (GObject *object)
{
  TpTestsContactsConnection *self = TP_TESTS_CONTACTS_CONNECTION (object);

  tp_contacts_mixin_finalize (object);
  g_hash_table_unref (self->priv->aliases);
  g_hash_table_unref (self->priv->avatars);
  g_hash_table_unref (self->priv->presence_statuses);
  g_hash_table_unref (self->priv->presence_messages);
  g_hash_table_unref (self->priv->locations);
  g_hash_table_unref (self->priv->capabilities);
  g_hash_table_unref (self->priv->contact_info);

  if (self->priv->default_contact_info != NULL)
    g_ptr_array_unref (self->priv->default_contact_info);

  G_OBJECT_CLASS (tp_tests_contacts_connection_parent_class)->finalize (object);
}
