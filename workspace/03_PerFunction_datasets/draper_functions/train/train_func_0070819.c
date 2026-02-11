dconf_libdbus_1_interpret_result (DBusMessage         *result,
                                  const GVariantType  *expected_type,
                                  GError             **error)
{
  GVariant *reply;

  if (dbus_message_get_type (result) == DBUS_MESSAGE_TYPE_ERROR)
    {
      const gchar *errstr = "(no message)";

      dbus_message_get_args (result, NULL, DBUS_TYPE_STRING, &errstr, DBUS_TYPE_INVALID);
      g_set_error (error, DCONF_LIBDBUS_1_ERROR, DCONF_LIBDBUS_1_ERROR_FAILED,
                   "%s: %s", dbus_message_get_error_name (result), errstr);
      return NULL;
    }

  reply = dconf_libdbus_1_get_message_body (result, error);

  if (reply && expected_type && !g_variant_is_of_type (reply, expected_type))
    {
      gchar *expected_string;

      expected_string = g_variant_type_dup_string (expected_type);
      g_set_error (error, DCONF_LIBDBUS_1_ERROR, DCONF_LIBDBUS_1_ERROR_FAILED,
                   "received reply '%s' is not of the expected type %s",
                   g_variant_get_type_string (reply), expected_string);
      g_free (expected_string);

      g_variant_unref (reply);
      reply = NULL;
    }

  return reply;
}
