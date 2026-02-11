remove_match(const char	*rule,
                              bool		throw_on_error)
{
  InternalError e;

  dbus_bus_remove_match(_pvt->conn, rule, e);

  debug_log("%s: removed match rule %s", unique_name(), rule);

  if (e)
  {
    if (throw_on_error)
      throw Error(e);
    else
      debug_log("DBus::Connection::remove_match: %s (%s).",
                static_cast<DBusError *>(e)->message,
                static_cast<DBusError *>(e)->name);
  }
}
