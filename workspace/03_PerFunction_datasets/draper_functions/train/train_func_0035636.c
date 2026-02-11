tp_dbus_check_valid_interface_name (const gchar *name,
                                    GError **error)
{
  gboolean dot = FALSE;
  gchar last;
  const gchar *ptr;

  g_return_val_if_fail (name != NULL, FALSE);

  if (name[0] == '\0')
    {
      g_set_error (error, TP_DBUS_ERRORS, TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
          "The empty string is not a valid interface name");
      return FALSE;
    }

  if (strlen (name) > 255)
    {
      g_set_error (error, TP_DBUS_ERRORS, TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
          "Invalid interface name: too long (> 255 characters)");
      return FALSE;
    }

  last = '\0';

  for (ptr = name; *ptr != '\0'; ptr++)
    {
      if (*ptr == '.')
        {
          dot = TRUE;

          if (last == '.')
            {
              g_set_error (error, TP_DBUS_ERRORS,
                  TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
                  "Invalid interface name '%s': contains '..'", name);
              return FALSE;
            }
          else if (last == '\0')
            {
              g_set_error (error, TP_DBUS_ERRORS,
                  TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
                  "Invalid interface name '%s': must not start with '.'",
                  name);
              return FALSE;
            }
        }
      else if (g_ascii_isdigit (*ptr))
        {
          if (last == '\0')
            {
              g_set_error (error, TP_DBUS_ERRORS,
                  TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
                  "Invalid interface name '%s': must not start with a digit",
                  name);
              return FALSE;
            }
          else if (last == '.')
            {
              g_set_error (error, TP_DBUS_ERRORS,
                  TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
                  "Invalid interface name '%s': a digit must not follow '.'",
                  name);
              return FALSE;
            }
        }
      else if (!g_ascii_isalpha (*ptr) && *ptr != '_')
        {
          g_set_error (error, TP_DBUS_ERRORS,
              TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
              "Invalid interface name '%s': contains invalid character '%c'",
              name, *ptr);
          return FALSE;
        }

      last = *ptr;
    }

  if (last == '.')
    {
      g_set_error (error, TP_DBUS_ERRORS, TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
          "Invalid interface name '%s': must not end with '.'", name);
      return FALSE;
    }

  if (!dot)
    {
      g_set_error (error, TP_DBUS_ERRORS, TP_DBUS_ERROR_INVALID_INTERFACE_NAME,
          "Invalid interface name '%s': must contain '.'", name);
      return FALSE;
    }

  return TRUE;
}
