_dbus_unpack_uint32 (int                  byte_order,
                     const unsigned char *data)
{
  _dbus_assert (_DBUS_ALIGN_ADDRESS (data, 4) == data);

  if (byte_order == DBUS_LITTLE_ENDIAN)
    return DBUS_UINT32_FROM_LE (*(dbus_uint32_t*)data);
  else
    return DBUS_UINT32_FROM_BE (*(dbus_uint32_t*)data);
}
