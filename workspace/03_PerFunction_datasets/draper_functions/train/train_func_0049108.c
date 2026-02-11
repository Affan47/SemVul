_dbus_data_slot_allocator_free (DBusDataSlotAllocator *allocator,
                                dbus_int32_t          *slot_id_p)
{
  _dbus_rmutex_lock (*(allocator->lock_loc));

  _dbus_assert (*slot_id_p < allocator->n_allocated_slots);
  _dbus_assert (allocator->allocated_slots[*slot_id_p].slot_id == *slot_id_p);
  _dbus_assert (allocator->allocated_slots[*slot_id_p].refcount > 0);

  allocator->allocated_slots[*slot_id_p].refcount -= 1;

  if (allocator->allocated_slots[*slot_id_p].refcount > 0)
    {
      _dbus_rmutex_unlock (*(allocator->lock_loc));
      return;
    }


  _dbus_verbose ("Freeing slot %d on allocator %p total %d allocated %d used\n",
                 *slot_id_p, allocator, allocator->n_allocated_slots, allocator->n_used_slots);

  allocator->allocated_slots[*slot_id_p].slot_id = -1;
  *slot_id_p = -1;

  allocator->n_used_slots -= 1;

  if (allocator->n_used_slots == 0)
    {
      DBusRMutex **mutex_loc = allocator->lock_loc;

      dbus_free (allocator->allocated_slots);
      allocator->allocated_slots = NULL;
      allocator->n_allocated_slots = 0;
      allocator->lock_loc = NULL;

      _dbus_rmutex_unlock (*mutex_loc);
    }
  else
    {
      _dbus_rmutex_unlock (*(allocator->lock_loc));
    }
}
