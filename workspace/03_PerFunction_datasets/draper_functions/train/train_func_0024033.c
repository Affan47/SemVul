_dbus_credentials_new (void)
{
  DBusCredentials *creds;

  creds = dbus_new (DBusCredentials, 1);
  if (creds == NULL)
    return NULL;

  creds->refcount = 1;
  creds->unix_uid = DBUS_UID_UNSET;
  creds->unix_pid = DBUS_PID_UNSET;
  creds->windows_sid = NULL;
  creds->adt_audit_data = NULL;
  creds->adt_audit_data_size = 0;

  return creds;
}
