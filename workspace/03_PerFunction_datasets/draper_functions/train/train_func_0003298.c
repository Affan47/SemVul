check_service_name (BusDesktopFile *desktop_file,
                    const char     *service_name,
                    DBusError      *error)
{
  char *name_tmp;
  dbus_bool_t retval;

  retval = FALSE;


  if (!bus_desktop_file_get_string (desktop_file,
                                    DBUS_SERVICE_SECTION,
                                    DBUS_SERVICE_NAME,
                                    &name_tmp,
                                    error))
    goto failed;


  if (strcmp (service_name, name_tmp) != 0)
    {
      dbus_set_error (error, DBUS_ERROR_SPAWN_FILE_INVALID,
                      "Service '%s' does not match expected value", name_tmp);
      goto failed_free;
    }

  retval = TRUE;

failed_free:

  dbus_free (name_tmp);
failed:
  return retval;
}
