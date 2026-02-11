_dbus_list_length_is_one (DBusList **list)
{
  return (*list != NULL &&
          (*list)->next == *list);
}
