writer_recurse_struct_or_dict_entry (DBusTypeWriter   *writer,
                                     int               begin_char,
                                     const DBusString *contained_type,
                                     int               contained_type_start,
                                     int               contained_type_len,
                                     DBusTypeWriter   *sub)
{


  if (writer->enabled)
    {
      if (!_dbus_string_alloc_space (sub->value_str, 8))
        return FALSE;
    }

  if (!write_or_verify_typecode (sub, begin_char))
    _dbus_assert_not_reached ("failed to insert struct typecode after prealloc");

  if (writer->enabled)
    {
      if (!_dbus_string_insert_bytes (sub->value_str,
                                      sub->value_pos,
                                      _DBUS_ALIGN_VALUE (sub->value_pos, 8) - sub->value_pos,
                                      '\0'))
        _dbus_assert_not_reached ("should not have failed to insert alignment padding for struct");
      sub->value_pos = _DBUS_ALIGN_VALUE (sub->value_pos, 8);
    }

  return TRUE;
}
