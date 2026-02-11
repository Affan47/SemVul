tp_group_mixin_remove_members_with_reason (GObject *obj,
                               const GArray *contacts,
                               const gchar *message,
                               guint reason,
                               GError **error)
{
  TpGroupMixinClass *mixin_cls = TP_GROUP_MIXIN_CLASS (G_OBJECT_GET_CLASS (obj));
  TpGroupMixin *mixin = TP_GROUP_MIXIN (obj);
  guint i;
  TpHandle handle;


  if (!tp_handles_are_valid (mixin->handle_repo, contacts, FALSE, error))
    return FALSE;


  for (i = 0; i < contacts->len; i++)
    {
      handle = g_array_index (contacts, TpHandle, i);

      if (mixin_cls->priv->allow_self_removal &&
          handle == mixin->self_handle &&
          (tp_handle_set_is_member (mixin->members, handle) ||
           tp_handle_set_is_member (mixin->remote_pending, handle) ||
           tp_handle_set_is_member (mixin->local_pending, handle)))
        {


        }
      else if (tp_handle_set_is_member (mixin->members, handle))
        {
          if ((mixin->group_flags & TP_CHANNEL_GROUP_FLAG_CAN_REMOVE) == 0)
            {
              DEBUG ("handle %u cannot be removed from members without "
                  "GROUP_FLAG_CAN_REMOVE", handle);

              g_set_error (error, TP_ERROR, TP_ERROR_PERMISSION_DENIED,
                  "handle %u cannot be removed from members without "
                  "GROUP_FLAG_CAN_REMOVE", handle);

              return FALSE;
            }
        }
      else if (tp_handle_set_is_member (mixin->remote_pending, handle))
        {
          if ((mixin->group_flags & TP_CHANNEL_GROUP_FLAG_CAN_RESCIND) == 0)
            {
              DEBUG ("handle %u cannot be removed from remote pending "
                  "without GROUP_FLAG_CAN_RESCIND", handle);

              g_set_error (error, TP_ERROR, TP_ERROR_PERMISSION_DENIED,
                  "handle %u cannot be removed from remote pending without "
                  "GROUP_FLAG_CAN_RESCIND", handle);

              return FALSE;
            }
        }
      else if (!tp_handle_set_is_member (mixin->local_pending, handle))
        {
          DEBUG ("handle %u is not a current or pending member",
                   handle);

        }
    }


  for (i = 0; i < contacts->len; i++)
    {
      handle = g_array_index (contacts, TpHandle, i);

      if (!tp_handle_set_is_member (mixin->members, handle) &&
          !tp_handle_set_is_member (mixin->remote_pending, handle) &&
          !tp_handle_set_is_member (mixin->local_pending, handle))
        continue;

      if (mixin_cls->priv->remove_with_reason != NULL)
        {
          if (!mixin_cls->priv->remove_with_reason (obj, handle, message,
                                                    reason, error))
            {
              return FALSE;
            }
        }
      else if (mixin_cls->remove_member != NULL)
        {
          if (!mixin_cls->remove_member (obj, handle, message, error))
            {
              return FALSE;
            }
        }
      else
        {
          g_set_error (error, TP_ERROR, TP_ERROR_NOT_IMPLEMENTED,
              "Removing contacts from this Group channel is not possible");
          return FALSE;
        }
    }

  return TRUE;
}
