dump_interface_type (GType type, const char *symbol, GOutputStream *out)
{
  guint n_interfaces;
  guint i;
  GType *interfaces;

  escaped_printf (out, "  <interface name=\"%s\" get-type=\"%s\">\n",
		  g_type_name (type), symbol);

  interfaces = g_type_interface_prerequisites (type, &n_interfaces);
  for (i = 0; i < n_interfaces; i++)
    {
      GType itype = interfaces[i];
      if (itype == G_TYPE_OBJECT)
	{


	  continue;
	}
      escaped_printf (out, "    <prerequisite name=\"%s\"/>\n",
		      g_type_name (itype));
    }
  dump_properties (type, out);
  dump_signals (type, out);
  goutput_write (out, "  </interface>\n");
}
