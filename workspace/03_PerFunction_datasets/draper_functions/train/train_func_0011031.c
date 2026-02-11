_dbus_message_iter_open_signature (DBusMessageRealIter *real)
{
  DBusString *str;
  const DBusString *current_sig;
  int current_sig_pos;

  _dbus_assert (real->iter_type == DBUS_MESSAGE_ITER_TYPE_WRITER);

  if (real->u.writer.type_str != NULL)
    {
      _dbus_assert (real->sig_refcount > 0);
      real->sig_refcount += 1;
      return TRUE;
    }

  str = dbus_new (DBusString, 1);
  if (str == NULL)
    return FALSE;

  if (!_dbus_header_get_field_raw (&real->message->header,
                                   DBUS_HEADER_FIELD_SIGNATURE,
                                   &current_sig, &current_sig_pos))
    current_sig = NULL;

  if (current_sig)
    {
      int current_len;

      current_len = _dbus_string_get_byte (current_sig, current_sig_pos);
      current_sig_pos += 1;

      if (!_dbus_string_init_preallocated (str, current_len + 4))
        {
          dbus_free (str);
          return FALSE;
        }

      if (!_dbus_string_copy_len (current_sig, current_sig_pos, current_len,
                                  str, 0))
        {
          _dbus_string_free (str);
          dbus_free (str);
          return FALSE;
        }
    }
  else
    {
      if (!_dbus_string_init_preallocated (str, 4))
        {
          dbus_free (str);
          return FALSE;
        }
    }

  real->sig_refcount = 1;

  _dbus_type_writer_add_types (&real->u.writer,
                               str, _dbus_string_get_length (str));
  return TRUE;
}
