mx_scrollable_base_init (gpointer g_iface)
{
  static gboolean initialized = FALSE;

  if (!initialized)
    {
      GParamSpec *pspec;
      pspec = g_param_spec_object ("horizontal-adjustment",
                                   "Horizontal adjustment",
                                   "The MxAdjustment for horizontal scrolling.",
                                   MX_TYPE_ADJUSTMENT,
                                   MX_PARAM_READWRITE);
      g_object_interface_install_property (g_iface, pspec);

      pspec = g_param_spec_object ("vertical-adjustment",
                                   "Vertical adjustment",
                                   "The MxAdjustment for vertical scrolling.",
                                   MX_TYPE_ADJUSTMENT,
                                   MX_PARAM_READWRITE);
      g_object_interface_install_property (g_iface, pspec);

      initialized = TRUE;
    }
}
