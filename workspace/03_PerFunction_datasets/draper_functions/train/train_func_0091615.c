bus_matchmaker_remove_rule_by_value (BusMatchmaker   *matchmaker,
                                     BusMatchRule    *value,
                                     DBusError       *error)
{
  DBusList **rules;
  DBusList *link = NULL;

  _dbus_verbose ("Removing rule by value with message_type %d, interface %s\n",
                 value->message_type,
                 value->interface != NULL ? value->interface : "<null>");

  rules = bus_matchmaker_get_rules (matchmaker, value->message_type,
      value->interface, FALSE);

  if (rules != NULL)
    {


      link = _dbus_list_get_last_link (rules);
      while (link != NULL)
        {
          BusMatchRule *rule;
          DBusList *prev;

          rule = link->data;
          prev = _dbus_list_get_prev_link (rules, link);

          if (match_rule_equal (rule, value))
            {
              bus_matchmaker_remove_rule_link (rules, link);
              break;
            }

          link = prev;
        }
    }

  if (link == NULL)
    {
      dbus_set_error (error, DBUS_ERROR_MATCH_RULE_NOT_FOUND,
                      "The given match rule wasn't found and can't be removed");
      return FALSE;
    }

  bus_matchmaker_gc_rules (matchmaker, value->message_type, value->interface,
      rules);

  return TRUE;
}
