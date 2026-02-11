tp_connection_get_detailed_error (TpConnection *self,
    const GHashTable **details)
{
  TpProxy *proxy = (TpProxy *) self;

  if (proxy->invalidated == NULL)
    return NULL;

  if (self->priv->connection_error != NULL)
    {
      g_assert (self->priv->connection_error_details != NULL);

      if (details != NULL)
        *details = self->priv->connection_error_details;

      return self->priv->connection_error;
    }
  else
    {


      if (details != NULL)
        {
          if (self->priv->connection_error_details == NULL)
            {
              self->priv->connection_error_details = tp_asv_new (
                  "debug-message", G_TYPE_STRING, proxy->invalidated->message,
                  NULL);
            }

          *details = self->priv->connection_error_details;
        }

      if (proxy->invalidated->domain == TP_ERROR)
        {
          return tp_error_get_dbus_name (proxy->invalidated->code);
        }
      else if (proxy->invalidated->domain == TP_DBUS_ERRORS)
        {
          switch (proxy->invalidated->code)
            {
            case TP_DBUS_ERROR_NAME_OWNER_LOST:

              return DBUS_ERROR_NO_REPLY;
              break;

            case TP_DBUS_ERROR_OBJECT_REMOVED:
            case TP_DBUS_ERROR_UNKNOWN_REMOTE_ERROR:
            case TP_DBUS_ERROR_INCONSISTENT:


            default:
              return TP_ERROR_STR_DISCONNECTED;
            }
        }
      else
        {

          return TP_ERROR_STR_DISCONNECTED;
        }
    }
}
