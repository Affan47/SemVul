ga_protocol_get_type (void)
{
  static GType etype = 0;
  if (etype == 0) {
    static const GEnumValue values[] = {
      { GA_PROTOCOL_INET, "GA_PROTOCOL_INET", "GA_PROTOCOL_INET" },
      { GA_PROTOCOL_INET6, "GA_PROTOCOL_INET6", "GA_PROTOCOL_INET6" },
      { GA_PROTOCOL_UNSPEC, "GA_PROTOCOL_UNSPEC", "GA_PROTOCOL_UNSPEC" },
      { 0, NULL, NULL }
    };
    etype = g_enum_register_static ("GaProtocol", values);
  }
  return etype;
}
