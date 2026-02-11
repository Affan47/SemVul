tp_base_contact_list_request_helper (TpChannelManager *manager,
    gpointer request_token,
    GHashTable *request_properties,
    gboolean is_create)
{
  TpBaseContactList *self = (TpBaseContactList *) manager;
  TpHandleType handle_type;
  TpHandle handle;
  TpBaseContactListChannel *chan;
  GError *error = NULL;

  g_return_val_if_fail (TP_IS_BASE_CONTACT_LIST (self), FALSE);

  if (tp_strdiff (tp_asv_get_string (request_properties,
          TP_PROP_CHANNEL_CHANNEL_TYPE),
      TP_IFACE_CHANNEL_TYPE_CONTACT_LIST))
    {
      return FALSE;
    }

  handle_type = tp_asv_get_uint32 (request_properties,
      TP_PROP_CHANNEL_TARGET_HANDLE_TYPE, NULL);

  if (handle_type != TP_HANDLE_TYPE_LIST &&
      (handle_type != TP_HANDLE_TYPE_GROUP ||
       !TP_IS_CONTACT_GROUP_LIST (self)))
    {
      return FALSE;
    }

  handle = tp_asv_get_uint32 (request_properties,
      TP_PROP_CHANNEL_TARGET_HANDLE, NULL);
  g_assert (handle != 0);

  if (tp_channel_manager_asv_has_unknown_properties (request_properties,
        fixed_properties, allowed_properties, &error) ||
      tp_base_contact_list_get_connection (self, &error) == NULL)
    {
      goto error;
    }

  if (handle_type == TP_HANDLE_TYPE_LIST)
    {

      g_assert (handle > 0);
      g_assert (handle < TP_NUM_LIST_HANDLES);

      if (handle == TP_LIST_HANDLE_STORED &&
          !tp_base_contact_list_get_contact_list_persists (self))
        {
          g_set_error_literal (&error, TP_ERROR, TP_ERROR_NOT_IMPLEMENTED,
              "Subscriptions do not persist, so this connection lacks the "
              "'stored' channel");
          goto error;
        }

      if (handle == TP_LIST_HANDLE_DENY &&
          !tp_base_contact_list_can_block (self))
        {
          g_set_error_literal (&error, TP_ERROR, TP_ERROR_NOT_IMPLEMENTED,
              "This connection cannot put people on the 'deny' list");
          goto error;
        }

      chan = self->priv->lists[handle];
    }
  else
    {
      chan = g_hash_table_lookup (self->priv->groups,
          GUINT_TO_POINTER (handle));
    }

  if (chan == NULL)
    {
      if (handle_type == TP_HANDLE_TYPE_LIST)
        {


          tp_base_contact_list_new_channel (self, handle_type, handle,
              request_token);
        }
      else
        {
          if (TP_IS_MUTABLE_CONTACT_GROUP_LIST (self))
            {
              const gchar *name = tp_handle_inspect (self->priv->group_repo,
                  handle);
              gpointer channel;
              TpHandleSet *set = tp_handle_set_new (self->priv->contact_repo);


              channel = tp_base_contact_list_new_channel (self, handle_type,
                  handle, request_token);


              tp_base_contact_list_add_to_group_async (self, name, set,
                  tp_base_contact_list_create_group_cb, channel);
              tp_handle_set_destroy (set);
            }
          else
            {
              g_set_error_literal (&error, TP_ERROR, TP_ERROR_NOT_IMPLEMENTED,
                  "This connection cannot create new groups");
              goto error;
            }
        }
    }
  else if (is_create)
    {
      g_set_error (&error, TP_ERROR, TP_ERROR_NOT_AVAILABLE,
          "A ContactList channel for type #%u, handle #%u already exists",
          handle_type, handle);
      goto error;
    }
  else if (g_hash_table_lookup_extended (self->priv->channel_requests, chan,
        NULL, NULL))
    {


      tp_base_contact_list_associate_request (self, chan, request_token);
    }
  else
    {
      tp_channel_manager_emit_request_already_satisfied (self,
          request_token, TP_EXPORTABLE_CHANNEL (chan));
    }

  return TRUE;

error:
  tp_channel_manager_emit_request_failed (self, request_token,
      error->domain, error->code, error->message);
  g_error_free (error);
  return TRUE;
}
