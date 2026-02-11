dbus_connection_free_data_slot (dbus_int32_t *slot_p)
{
  _dbus_return_if_fail (*slot_p >= 0);

  _dbus_data_slot_allocator_free (&slot_allocator, slot_p);
}
