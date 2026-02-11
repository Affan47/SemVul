apply_and_free_fixups (DBusList      **fixups,
                       DBusTypeReader *reader)
{
  DBusList *link;

#if RECURSIVE_MARSHAL_WRITE_TRACE
  if (*fixups)
    _dbus_verbose (" %d FIXUPS to apply\n",
                   _dbus_list_get_length (fixups));
#endif

  link = _dbus_list_get_first_link (fixups);
  while (link != NULL)
    {
      DBusList *next;

      next = _dbus_list_get_next_link (fixups, link);

      if (reader)
        {
          DBusArrayLenFixup *f;

          f = link->data;

#if RECURSIVE_MARSHAL_WRITE_TRACE
          _dbus_verbose (" applying FIXUP to reader %p at pos %d new_len = %d old len %d\n",
                         reader, f->len_pos_in_reader, f->new_len,
                         _dbus_marshal_read_uint32 (reader->value_str,
                                                    f->len_pos_in_reader,
                                                    reader->byte_order, NULL));
#endif

          _dbus_marshal_set_uint32 ((DBusString*) reader->value_str,
                                    f->len_pos_in_reader,
                                    f->new_len,
                                    reader->byte_order);
        }

      dbus_free (link->data);
      _dbus_list_free_link (link);

      link = next;
    }

  *fixups = NULL;
}
