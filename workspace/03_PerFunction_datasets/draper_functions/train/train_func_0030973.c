get_recipients_from_list (DBusList       **rules,
                          DBusConnection  *sender,
                          DBusConnection  *addressed_recipient,
                          DBusMessage     *message,
                          DBusList       **recipients_p)
{
  DBusList *link;

  if (rules == NULL)
    return TRUE;

  link = _dbus_list_get_first_link (rules);
  while (link != NULL)
    {
      BusMatchRule *rule;

      rule = link->data;

#ifdef DBUS_ENABLE_VERBOSE_MODE
      {
        char *s = match_rule_to_string (rule);

        _dbus_verbose ("Checking whether message matches rule %s for connection %p\n",
                       s, rule->matches_go_to);
        dbus_free (s);
      }
#endif

      if (match_rule_matches (rule,
                              sender, addressed_recipient, message,
                              BUS_MATCH_MESSAGE_TYPE | BUS_MATCH_INTERFACE))
        {
          _dbus_verbose ("Rule matched\n");


          if (bus_connection_mark_stamp (rule->matches_go_to))
            {
              if (!_dbus_list_append (recipients_p, rule->matches_go_to))
                return FALSE;
            }
#ifdef DBUS_ENABLE_VERBOSE_MODE
          else
            {
              _dbus_verbose ("Connection already receiving this message, so not adding again\n");
            }
#endif
        }

      link = _dbus_list_get_next_link (rules, link);
    }

  return TRUE;
}
