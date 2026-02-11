dbus_type_is_fixed (int typecode)
{

  _dbus_return_val_if_fail (dbus_type_is_valid (typecode) || typecode == DBUS_TYPE_INVALID,
			    FALSE);

  switch (typecode)
    {
    case DBUS_TYPE_BYTE:
    case DBUS_TYPE_BOOLEAN:
    case DBUS_TYPE_INT16:
    case DBUS_TYPE_UINT16:
    case DBUS_TYPE_INT32:
    case DBUS_TYPE_UINT32:
    case DBUS_TYPE_INT64:
    case DBUS_TYPE_UINT64:
    case DBUS_TYPE_DOUBLE:
    case DBUS_TYPE_UNIX_FD:
      return TRUE;
    default:
      return FALSE;
    }
}
