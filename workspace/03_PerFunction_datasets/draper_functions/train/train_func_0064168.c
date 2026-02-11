print_plugin_automatic_install_info_protocols (GstElementFactory * factory)
{
  gchar **protocols, **p;

  protocols = gst_element_factory_get_uri_protocols (factory);
  if (protocols != NULL && *protocols != NULL) {
    switch (gst_element_factory_get_uri_type (factory)) {
      case GST_URI_SINK:
        for (p = protocols; *p != NULL; ++p)
          g_print ("urisink-%s\n", *p);
        break;
      case GST_URI_SRC:
        for (p = protocols; *p != NULL; ++p)
          g_print ("urisource-%s\n", *p);
        break;
      default:
        break;
    }
    g_strfreev (protocols);
  }
}
