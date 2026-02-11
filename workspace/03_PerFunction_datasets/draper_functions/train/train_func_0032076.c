_dbus_list_unlink (DBusList **list,
                   DBusList  *link)
{
  if (link->next == link)
    {

      *list = NULL;
    }
  else
    {
      link->prev->next = link->next;
      link->next->prev = link->prev;

      if (*list == link)
        *list = link->next;
    }

  link->next = NULL;
  link->prev = NULL;
}
