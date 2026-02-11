tp_g_socket_address_from_variant (TpSocketAddressType type,
    const GValue *variant,
    GError **error)
{
  GSocketAddress *addr;

  switch (type)
    {
#ifdef HAVE_GIO_UNIX
      case TP_SOCKET_ADDRESS_TYPE_UNIX:
        if (!G_VALUE_HOLDS (variant, DBUS_TYPE_G_UCHAR_ARRAY))
          {
            g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
                "variant is %s not DBUS_TYPE_G_UCHAR_ARRAY",
                G_VALUE_TYPE_NAME (variant));

            return NULL;
          }
        else
          {
            GArray *address = g_value_get_boxed (variant);
            char path[address->len + 1];

            strncpy (path, address->data, address->len);
            path[address->len] = '\0';

            addr = g_unix_socket_address_new (path);
          }
        break;

      case TP_SOCKET_ADDRESS_TYPE_ABSTRACT_UNIX:
        if (!G_VALUE_HOLDS (variant, DBUS_TYPE_G_UCHAR_ARRAY))
          {
            g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
                "variant is %s not DBUS_TYPE_G_UCHAR_ARRAY",
                G_VALUE_TYPE_NAME (variant));

            return NULL;
          }
        else
          {
            GArray *address = g_value_get_boxed (variant);

            addr = g_unix_socket_address_new_with_type (
                address->data, address->len, G_UNIX_SOCKET_ADDRESS_ABSTRACT);
          }
        break;
#endif

      case TP_SOCKET_ADDRESS_TYPE_IPV4:
      case TP_SOCKET_ADDRESS_TYPE_IPV6:
        if (type == TP_SOCKET_ADDRESS_TYPE_IPV4 &&
            !G_VALUE_HOLDS (variant, TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV4))
          {
            g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
                "variant is %s not TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV4",
                G_VALUE_TYPE_NAME (variant));

            return NULL;
          }
        else if (type == TP_SOCKET_ADDRESS_TYPE_IPV6 &&
            !G_VALUE_HOLDS (variant, TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV6))
          {
            g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
                "variant is %s not TP_STRUCT_TYPE_SOCKET_ADDRESS_IPV6",
                G_VALUE_TYPE_NAME (variant));

            return NULL;
          }
        else
          {
            GValueArray *array = g_value_get_boxed (variant);
            GValue *hostv = g_value_array_get_nth (array, 0);
            GValue *portv = g_value_array_get_nth (array, 1);
            GInetAddress *address;
            const char *host;
            guint16 port;

            g_return_val_if_fail (G_VALUE_HOLDS_STRING (hostv), NULL);
            g_return_val_if_fail (G_VALUE_HOLDS_UINT (portv), NULL);

            host = g_value_get_string (hostv);
            port = g_value_get_uint (portv);

            address = g_inet_address_new_from_string (host);
            addr = g_inet_socket_address_new (address, port);

            g_object_unref (address);
          }
        break;

      default:
        g_set_error (error, TP_ERROR, TP_ERROR_INVALID_ARGUMENT,
            "Unknown TpSocketAddressType (%i)",
            type);

        return NULL;
    }

  return addr;
}
