_dbus_list_get_length (DBusList **list)
{
  DBusList *link;
  int length;

  length = 0;

  link = *list;
  while (link != NULL)
    {
      ++length;

      link = _dbus_list_get_next_link (list, link);
    }

  return length;
}
