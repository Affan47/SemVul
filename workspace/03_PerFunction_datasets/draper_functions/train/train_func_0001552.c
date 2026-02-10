free_rule_list_func (void *data)
{
  DBusList **list = data;

  if (list == NULL)
    return;

  _dbus_list_foreach (list, free_rule_func, NULL);

  _dbus_list_clear (list);

  dbus_free (list);
}
