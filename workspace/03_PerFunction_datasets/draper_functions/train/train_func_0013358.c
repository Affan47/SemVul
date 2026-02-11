e_dbus_timeout_data_free(void *timeout_data)
{
  E_DBus_Timeout_Data *td = timeout_data;
  DBG("e_dbus_timeout_data_free");
  if (td->handler) ecore_timer_del(td->handler);
  free(td);
}
