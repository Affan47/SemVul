write_or_verify_typecode (DBusTypeWriter *writer,
                          int             typecode)
{


#if RECURSIVE_MARSHAL_WRITE_TRACE
  _dbus_verbose ("  type writer %p write_or_verify start type_pos = %d remaining sig '%s' enabled = %d\n",
                 writer, writer->type_pos,
                 writer->type_str ?
                 _dbus_string_get_const_data_len (writer->type_str, writer->type_pos, 0) :
                 "unknown",
                 writer->enabled);
#endif

  if (writer->type_str == NULL)
    return TRUE;

  if (writer->type_pos_is_expectation)
    {
#ifndef DBUS_DISABLE_CHECKS
      {
        int expected;

        expected = _dbus_string_get_byte (writer->type_str, writer->type_pos);

        if (expected != typecode)
          {
            if (expected != DBUS_TYPE_INVALID)
              _dbus_warn_check_failed ("Array or variant type requires that type %s be written, but %s was written.\n"
                                       "The overall signature expected here was '%s' and we are on byte %d of that signature.\n",
                                       _dbus_type_to_string (expected), _dbus_type_to_string (typecode),
                                       _dbus_string_get_const_data (writer->type_str), writer->type_pos);
            else
              _dbus_warn_check_failed ("Array or variant type wasn't expecting any more values to be written into it, but a value %s was written.\n"
                                       "The overall signature expected here was '%s' and we are on byte %d of that signature.\n",
                                       _dbus_type_to_string (typecode),
                                       _dbus_string_get_const_data (writer->type_str), writer->type_pos);
            _dbus_assert_not_reached ("bad type inserted somewhere inside an array or variant");
          }
      }
#endif


      if (writer->container_type != DBUS_TYPE_ARRAY)
        writer->type_pos += 1;
    }
  else
    {
      if (!_dbus_string_insert_byte (writer->type_str,
                                     writer->type_pos,
                                     typecode))
        return FALSE;

      writer->type_pos += 1;
    }

#if RECURSIVE_MARSHAL_WRITE_TRACE
  _dbus_verbose ("  type writer %p write_or_verify end type_pos = %d remaining sig '%s'\n",
                 writer, writer->type_pos,
                 _dbus_string_get_const_data_len (writer->type_str, writer->type_pos, 0));
#endif

  return TRUE;
}
