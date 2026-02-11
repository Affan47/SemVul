contacts_inspected (TpConnection *connection,
                    const gchar **ids,
                    const GError *error,
                    gpointer user_data,
                    GObject *weak_object)
{
  ContactsContext *c = user_data;

  g_assert (weak_object == c->weak_object);
  g_assert (c->handles->len == c->contacts->len);

  if (error != NULL)
    {

      contacts_context_fail (c, error);
      return;
    }
  else if (G_UNLIKELY (g_strv_length ((GStrv) ids) != c->handles->len))
    {
      GError *e = g_error_new (TP_DBUS_ERRORS, TP_DBUS_ERROR_INCONSISTENT,
          "Connection manager %s is broken: we inspected %u "
          "handles but InspectHandles returned %u strings",
          tp_proxy_get_bus_name (connection), c->handles->len,
          g_strv_length ((GStrv) ids));

      WARNING ("%s", e->message);
      contacts_context_fail (c, e);
      g_error_free (e);
      return;
    }
  else
    {
      guint i;

      for (i = 0; i < c->contacts->len; i++)
        {
          TpContact *contact = g_ptr_array_index (c->contacts, i);

          g_assert (ids[i] != NULL);

          if (contact->priv->identifier == NULL)
            {
              contact->priv->identifier = g_strdup (ids[i]);
            }
          else if (tp_strdiff (contact->priv->identifier, ids[i]))
            {
              GError *e = g_error_new (TP_DBUS_ERRORS,
                  TP_DBUS_ERROR_INCONSISTENT,
                  "Connection manager %s is broken: contact handle %u "
                  "identifier changed from %s to %s",
                  tp_proxy_get_bus_name (connection), contact->priv->handle,
                  contact->priv->identifier, ids[i]);

              WARNING ("%s", e->message);
              contacts_context_fail (c, e);
              g_error_free (e);
              return;
            }
        }
    }

  contacts_context_continue (c);
}
