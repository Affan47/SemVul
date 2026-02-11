bus_pending_activation_unref (BusPendingActivation *pending_activation)
{
  DBusList *link;

  if (pending_activation == NULL)
    return;

  _dbus_assert (pending_activation->refcount > 0);
  pending_activation->refcount -= 1;

  if (pending_activation->refcount > 0)
    return;

  if (pending_activation->timeout_added)
    {
      _dbus_loop_remove_timeout (bus_context_get_loop (pending_activation->activation->context),
                                 pending_activation->timeout);
      pending_activation->timeout_added = FALSE;
    }

  if (pending_activation->timeout)
    _dbus_timeout_unref (pending_activation->timeout);

  if (pending_activation->babysitter)
    {
      if (!_dbus_babysitter_set_watch_functions (pending_activation->babysitter,
                                                 NULL, NULL, NULL,
                                                 pending_activation->babysitter,
                                                 NULL))
        _dbus_assert_not_reached ("setting watch functions to NULL failed");

      _dbus_babysitter_unref (pending_activation->babysitter);
    }

  dbus_free (pending_activation->service_name);
  dbus_free (pending_activation->exec);
  dbus_free (pending_activation->systemd_service);

  link = _dbus_list_get_first_link (&pending_activation->entries);

  while (link != NULL)
    {
      BusPendingActivationEntry *entry = link->data;

      bus_pending_activation_entry_free (entry);

      link = _dbus_list_get_next_link (&pending_activation->entries, link);
    }
  _dbus_list_clear (&pending_activation->entries);

  pending_activation->activation->n_pending_activations -=
    pending_activation->n_entries;

  _dbus_assert (pending_activation->activation->n_pending_activations >= 0);

  dbus_free (pending_activation);
}
