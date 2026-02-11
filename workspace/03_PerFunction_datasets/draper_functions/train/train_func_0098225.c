print_all_uri_handlers (void)
{
  GList *plugins, *p, *features, *f;

  plugins = gst_default_registry_get_plugin_list ();

  for (p = plugins; p; p = p->next) {
    GstPlugin *plugin = (GstPlugin *) (p->data);

    features =
        gst_registry_get_feature_list_by_plugin (gst_registry_get_default (),
        plugin->desc.name);

    for (f = features; f; f = f->next) {
      GstPluginFeature *feature = GST_PLUGIN_FEATURE (f->data);

      if (GST_IS_ELEMENT_FACTORY (feature)) {
        GstElementFactory *factory;
        GstElement *element;

        factory = GST_ELEMENT_FACTORY (gst_plugin_feature_load (feature));
        if (!factory) {
          g_print ("element plugin %s couldn't be loaded\n", plugin->desc.name);
          continue;
        }

        element = gst_element_factory_create (factory, NULL);
        if (!element) {
          g_print ("couldn't construct element for %s for some reason\n",
              GST_OBJECT_NAME (factory));
          gst_object_unref (factory);
          continue;
        }

        if (GST_IS_URI_HANDLER (element)) {
          const gchar *dir;
          gchar **uri_protocols, *joined;

          switch (gst_uri_handler_get_uri_type (GST_URI_HANDLER (element))) {
            case GST_URI_SRC:
              dir = "read";
              break;
            case GST_URI_SINK:
              dir = "write";
              break;
            default:
              dir = "unknown";
              break;
          }

          uri_protocols =
              gst_uri_handler_get_protocols (GST_URI_HANDLER (element));
          joined = g_strjoinv (", ", uri_protocols);

          g_print ("%s (%s, rank %u): %s\n",
              gst_plugin_feature_get_name (GST_PLUGIN_FEATURE (factory)), dir,
              gst_plugin_feature_get_rank (GST_PLUGIN_FEATURE (factory)),
              joined);

          g_free (joined);
        }

        gst_object_unref (element);
        gst_object_unref (factory);
      }
    }

    gst_plugin_feature_list_free (features);
  }

  gst_plugin_list_free (plugins);
}
