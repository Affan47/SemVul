bus_config_parser_new (const DBusString      *basedir,
                       dbus_bool_t            is_toplevel,
                       const BusConfigParser *parent)
{
  BusConfigParser *parser;

  parser = dbus_new0 (BusConfigParser, 1);
  if (parser == NULL)
    return NULL;

  parser->is_toplevel = !!is_toplevel;

  if (!_dbus_string_init (&parser->basedir))
    {
      dbus_free (parser);
      return NULL;
    }

  if (((parser->policy = bus_policy_new ()) == NULL) ||
      !_dbus_string_copy (basedir, 0, &parser->basedir, 0) ||
      ((parser->service_context_table = _dbus_hash_table_new (DBUS_HASH_STRING,
							      dbus_free,
							      dbus_free)) == NULL))
    {
      if (parser->policy)
        bus_policy_unref (parser->policy);

      _dbus_string_free (&parser->basedir);

      dbus_free (parser);
      return NULL;
    }

  if (parent != NULL)
    {

      parser->limits = parent->limits;


      parser->included_files = parent->included_files;
    }
  else
    {


      parser->limits.max_incoming_bytes = _DBUS_ONE_MEGABYTE * 127;
      parser->limits.max_outgoing_bytes = _DBUS_ONE_MEGABYTE * 127;
      parser->limits.max_message_size = _DBUS_ONE_MEGABYTE * 32;


      parser->limits.max_incoming_unix_fds = 1024*4;
      parser->limits.max_outgoing_unix_fds = 1024*4;
      parser->limits.max_message_unix_fds = 1024;


      parser->limits.activation_timeout = 25000;


      parser->limits.auth_timeout = 30000;

      parser->limits.max_incomplete_connections = 64;
      parser->limits.max_connections_per_user = 256;


      parser->limits.max_completed_connections = 2048;

      parser->limits.max_pending_activations = 512;
      parser->limits.max_services_per_connection = 512;


      parser->limits.max_match_rules_per_connection = 512;

      parser->limits.reply_timeout = -1;


      parser->limits.max_replies_per_connection = 1024*8;
    }

  parser->refcount = 1;

  return parser;
}
