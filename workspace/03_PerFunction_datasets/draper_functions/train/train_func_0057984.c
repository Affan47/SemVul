bus_match_rule_unref (BusMatchRule *rule)
{
  _dbus_assert (rule->refcount > 0);

  rule->refcount -= 1;
  if (rule->refcount == 0)
    {
      dbus_free (rule->interface);
      dbus_free (rule->member);
      dbus_free (rule->sender);
      dbus_free (rule->destination);
      dbus_free (rule->path);
      dbus_free (rule->arg_lens);


      if (rule->args)
        {
          int i;

          i = 0;
          while (i < rule->args_len)
            {
              if (rule->args[i])
                dbus_free (rule->args[i]);
              ++i;
            }

          dbus_free (rule->args);
        }

      dbus_free (rule);
    }
}
