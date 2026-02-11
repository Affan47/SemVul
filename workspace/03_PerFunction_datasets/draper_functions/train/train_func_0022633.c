got_all_properties_cb (TpProxy *proxy,
    GHashTable *properties,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  TpCallContent *self = (TpCallContent *) proxy;
  const gchar * const *interfaces;
  GPtrArray *streams;
  guint i;

  if (error != NULL)
    {
      DEBUG ("Could not get the call content properties: %s", error->message);
      _tp_proxy_set_feature_prepared (proxy,
          TP_CALL_CONTENT_FEATURE_CORE, FALSE);
      return;
    }

  self->priv->properties_retrieved = TRUE;

  interfaces = tp_asv_get_boxed (properties,
      "Interfaces", G_TYPE_STRV);
  self->priv->name = g_strdup (tp_asv_get_string (properties,
      "Name"));
  self->priv->media_type = tp_asv_get_uint32 (properties,
      "Type", NULL);
  self->priv->disposition = tp_asv_get_uint32 (properties,
      "Disposition", NULL);
  streams = tp_asv_get_boxed (properties,
      "Streams", TP_ARRAY_TYPE_OBJECT_PATH_LIST);

  tp_proxy_add_interfaces ((TpProxy *) self, interfaces);

  for (i = 0; i < streams->len; i++)
    {
      const gchar *object_path = g_ptr_array_index (streams, i);

      DEBUG ("Initial stream added: %s", object_path);

      g_ptr_array_add (self->priv->streams,
          _tp_call_stream_new (self, object_path));
    }

  if (tp_proxy_has_interface_by_id (self,
          TP_IFACE_QUARK_CALL_CONTENT_INTERFACE_DTMF))
    {
      tp_cli_call_content_interface_dtmf_connect_to_stopped_tones (self,
          tones_stopped_cb, NULL, NULL, NULL, NULL);
    }

  _tp_proxy_set_feature_prepared (proxy, TP_CALL_CONTENT_FEATURE_CORE, TRUE);
}
