_dbus_credentials_add_credential (DBusCredentials    *credentials,
                                  DBusCredentialType  which,
                                  DBusCredentials    *other_credentials)
{
  if (which == DBUS_CREDENTIAL_UNIX_PROCESS_ID &&
      other_credentials->unix_pid != DBUS_PID_UNSET)
    {
      if (!_dbus_credentials_add_unix_pid (credentials, other_credentials->unix_pid))
        return FALSE;
    }
  else if (which == DBUS_CREDENTIAL_UNIX_USER_ID &&
           other_credentials->unix_uid != DBUS_UID_UNSET)
    {
      if (!_dbus_credentials_add_unix_uid (credentials, other_credentials->unix_uid))
        return FALSE;
    }
  else if (which == DBUS_CREDENTIAL_WINDOWS_SID &&
           other_credentials->windows_sid != NULL)
    {
      if (!_dbus_credentials_add_windows_sid (credentials, other_credentials->windows_sid))
        return FALSE;
    }
  else if (which == DBUS_CREDENTIAL_ADT_AUDIT_DATA_ID &&
           other_credentials->adt_audit_data != NULL)
    {
      if (!_dbus_credentials_add_adt_audit_data (credentials, other_credentials->adt_audit_data, other_credentials->adt_audit_data_size))
        return FALSE;
    }

  return TRUE;
}
