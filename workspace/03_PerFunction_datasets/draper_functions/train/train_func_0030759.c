gst_udpsink_set_property (GObject * object, guint prop_id, const GValue * value,
    GParamSpec * pspec)
{
  GstUDPSink *udpsink;

  udpsink = GST_UDPSINK (object);


  gst_multiudpsink_remove (GST_MULTIUDPSINK (udpsink),
      udpsink->host, udpsink->port);

  switch (prop_id) {
    case PROP_HOST:
    {
      const gchar *host;

      host = g_value_get_string (value);
      g_free (udpsink->host);
      udpsink->host = g_strdup (host);
      g_free (udpsink->uri);
      udpsink->uri =
          g_strdup_printf ("udp://%s:%d", udpsink->host, udpsink->port);
      break;
    }
    case PROP_PORT:
      udpsink->port = g_value_get_int (value);
      g_free (udpsink->uri);
      udpsink->uri =
          g_strdup_printf ("udp://%s:%d", udpsink->host, udpsink->port);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }

  gst_multiudpsink_add (GST_MULTIUDPSINK (udpsink),
      udpsink->host, udpsink->port);
}
