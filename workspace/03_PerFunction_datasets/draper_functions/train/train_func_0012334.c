inf_communication_method_base_init(gpointer class)
{
  static gboolean initialized = FALSE;

  if(!initialized)
  {


    method_signals[ADD_MEMBER] = g_signal_new(
      "add-member",
      INF_COMMUNICATION_TYPE_METHOD,
      G_SIGNAL_RUN_LAST,
      G_STRUCT_OFFSET(InfCommunicationMethodIface, add_member),
      NULL, NULL,
      inf_marshal_VOID__OBJECT,
      G_TYPE_NONE,
      1,
      INF_TYPE_XML_CONNECTION
    );


    method_signals[REMOVE_MEMBER] = g_signal_new(
      "remove-member",
      INF_COMMUNICATION_TYPE_METHOD,
      G_SIGNAL_RUN_LAST,
      G_STRUCT_OFFSET(InfCommunicationMethodIface, remove_member),
      NULL, NULL,
      inf_marshal_VOID__OBJECT,
      G_TYPE_NONE,
      1,
      INF_TYPE_XML_CONNECTION
    );

    initialized = TRUE;
  }
}
