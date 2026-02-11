add_restore_ownership_to_transaction (BusTransaction *transaction,
                                      BusService     *service,
                                      BusOwner       *owner)
{
  OwnershipRestoreData *d;
  DBusList *link;

  d = dbus_new (OwnershipRestoreData, 1);
  if (d == NULL)
    return FALSE;

  d->service = service;
  d->owner = owner;
  d->service_link = _dbus_list_alloc_link (service);
  d->owner_link = _dbus_list_alloc_link (owner);
  d->hash_entry = _dbus_hash_table_preallocate_entry (service->registry->service_hash);

  bus_service_ref (d->service);
  bus_owner_ref (d->owner);
  dbus_connection_ref (d->owner->conn);

  d->before_owner = NULL;
  link = _dbus_list_get_first_link (&service->owners);
  while (link != NULL)
    {
      if (link->data == owner)
        {
          link = _dbus_list_get_next_link (&service->owners, link);

          if (link)
            d->before_owner = link->data;

          break;
        }

      link = _dbus_list_get_next_link (&service->owners, link);
    }

  if (d->service_link == NULL ||
      d->owner_link == NULL ||
      d->hash_entry == NULL ||
      !bus_transaction_add_cancel_hook (transaction, restore_ownership, d,
                                        free_ownership_restore_data))
    {
      free_ownership_restore_data (d);
      return FALSE;
    }

  return TRUE;
}
