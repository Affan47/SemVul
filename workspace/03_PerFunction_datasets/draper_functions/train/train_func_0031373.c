inf_discovery_base_init(gpointer g_class)
{
  static gboolean initialized = FALSE;

  if(!initialized)
  {


    discovery_signals[DISCOVERED] = g_signal_new(
      "discovered",
      INF_TYPE_DISCOVERY,
      G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
      G_STRUCT_OFFSET(InfDiscoveryIface, discovered),
      NULL, NULL,
      inf_marshal_VOID__POINTER,
      G_TYPE_NONE,
      1,
      G_TYPE_POINTER
    );


    discovery_signals[UNDISCOVERED] = g_signal_new(
      "undiscovered",
      INF_TYPE_DISCOVERY,
      G_SIGNAL_RUN_LAST | G_SIGNAL_DETAILED,
      G_STRUCT_OFFSET(InfDiscoveryIface, undiscovered),
      NULL, NULL,
      inf_marshal_VOID__POINTER,
      G_TYPE_NONE,
      1,
      G_TYPE_POINTER
    );

    initialized = TRUE;
  }
}
