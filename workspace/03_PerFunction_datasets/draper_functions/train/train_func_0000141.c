_dbus_type_reader_read_raw (const DBusTypeReader  *reader,
                            const unsigned char  **value_location)
{
  _dbus_assert (!reader->klass->types_only);

  *value_location = _dbus_string_get_const_data_len (reader->value_str,
                                                     reader->value_pos,
                                                     0);
}
