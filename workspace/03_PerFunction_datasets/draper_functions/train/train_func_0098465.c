example_call_connection_manager_constructed (GObject *object)
{
  ExampleCallConnectionManager *self =
    EXAMPLE_CALL_CONNECTION_MANAGER (object);
  TpBaseConnectionManager *base = (TpBaseConnectionManager *) self;
  void (*constructed) (GObject *) =
    ((GObjectClass *) example_call_connection_manager_parent_class)->constructed;
  TpBaseProtocol *protocol;

  if (constructed != NULL)
    constructed (object);

  protocol = g_object_new (EXAMPLE_TYPE_CALL_PROTOCOL,
      "name", "example",
      NULL);
  tp_base_connection_manager_add_protocol (base, protocol);
  g_object_unref (protocol);
}
