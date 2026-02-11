sw_contact_view_dispose (GObject *object)
{
  SwContactViewPrivate *priv = GET_PRIVATE (object);

  if (priv->service)
  {
    g_object_unref (priv->service);
    priv->service = NULL;
  }

  if (priv->current_contacts_set)
  {
    sw_set_unref (priv->current_contacts_set);
    priv->current_contacts_set = NULL;
  }

  if (priv->pending_contacts_set)
  {
    sw_set_unref (priv->pending_contacts_set);
    priv->pending_contacts_set = NULL;
  }

  if (priv->uid_to_contacts)
  {
    g_hash_table_unref (priv->uid_to_contacts);
    priv->uid_to_contacts = NULL;
  }

  if (priv->pending_timeout_id)
  {
    g_source_remove (priv->pending_timeout_id);
    priv->pending_timeout_id = 0;
  }

  if (priv->refresh_timeout_id)
  {
    g_source_remove (priv->refresh_timeout_id);
    priv->refresh_timeout_id = 0;
  }

  G_OBJECT_CLASS (sw_contact_view_parent_class)->dispose (object);
}
