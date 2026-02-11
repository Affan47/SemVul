free_connection_data (void *data)
{
  BusConnectionData *d = data;


  _dbus_assert (d->services_owned == NULL);
  _dbus_assert (d->n_services_owned == 0);

  _dbus_assert (d->transaction_messages == NULL);

  if (d->oom_preallocated)
    dbus_connection_free_preallocated_send (d->connection, d->oom_preallocated);

  if (d->oom_message)
    dbus_message_unref (d->oom_message);

  if (d->policy)
    bus_client_policy_unref (d->policy);

  if (d->selinux_id)
    bus_selinux_id_unref (d->selinux_id);

  if (d->apparmor_confinement)
    bus_apparmor_confinement_unref (d->apparmor_confinement);

  dbus_free (d->cached_loginfo_string);

  dbus_free (d->name);

  dbus_free (d);
}
