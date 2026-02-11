_dbus_credentials_include (DBusCredentials    *credentials,
                           DBusCredentialType  type)
{
  switch (type)
    {
    case DBUS_CREDENTIAL_UNIX_PROCESS_ID:
      return credentials->unix_pid != DBUS_PID_UNSET;
    case DBUS_CREDENTIAL_UNIX_USER_ID:
      return credentials->unix_uid != DBUS_UID_UNSET;
    case DBUS_CREDENTIAL_WINDOWS_SID:
      return credentials->windows_sid != NULL;
    case DBUS_CREDENTIAL_ADT_AUDIT_DATA_ID:
      return credentials->adt_audit_data != NULL;
    }

  _dbus_assert_not_reached ("Unknown credential enum value");
  return FALSE;
}
