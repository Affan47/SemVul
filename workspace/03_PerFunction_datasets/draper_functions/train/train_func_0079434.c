contact_group_renamed_cb (TpConnection *self,
    const gchar *old_name,
    const gchar *new_name,
    gpointer user_data,
    GObject *weak_object)
{
  guint i;

  if (!self->priv->groups_fetched)
      return;

  DEBUG ("Group renamed: %s -> %s", old_name, new_name);


  g_ptr_array_remove_index_fast (self->priv->contact_groups,
      self->priv->contact_groups->len - 1);

  for (i = 0; i < self->priv->contact_groups->len; i++)
    {
      const gchar *str = g_ptr_array_index (self->priv->contact_groups, i);

      if (!tp_strdiff (str, old_name))
        {
          g_ptr_array_remove_index_fast (self->priv->contact_groups, i);
          break;
        }
    }
  g_ptr_array_add (self->priv->contact_groups, g_strdup (new_name));


  g_ptr_array_add (self->priv->contact_groups, NULL);

  g_object_notify ((GObject *) self, "contact-groups");
  g_signal_emit_by_name (self, "group-renamed", old_name, new_name);
}
