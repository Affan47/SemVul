swap_array (DBusString *str,
            int         array_start,
            int         n_elements,
            int         byte_order,
            int         alignment)
{
  _dbus_assert (_DBUS_ALIGN_VALUE (array_start, alignment) == (unsigned) array_start);

  if (byte_order != DBUS_COMPILER_BYTE_ORDER)
    {


      _dbus_swap_array ((unsigned char*) (_dbus_string_get_const_data (str) + array_start),
                        n_elements, alignment);
    }
}
