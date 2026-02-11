fs_rawudp_stream_transmitter_set_property (GObject *object,
    guint prop_id,
    const GValue *value,
    GParamSpec *pspec)
{
  FsRawUdpStreamTransmitter *self = FS_RAWUDP_STREAM_TRANSMITTER (object);

  switch (prop_id)
  {
    case PROP_SENDING:
      {
        gint c;

        self->priv->sending = g_value_get_boolean (value);

        for (c = 1; c <= self->priv->transmitter->components; c++)
          if (self->priv->component[c])
            g_object_set_property (G_OBJECT (self->priv->component[c]),
                "sending", value);
      }
      break;
    case PROP_PREFERRED_LOCAL_CANDIDATES:
      self->priv->preferred_local_candidates = g_value_dup_boxed (value);
      break;
    case PROP_ASSOCIATE_ON_SOURCE:
      self->priv->associate_on_source = g_value_get_boolean (value);
      break;
    case PROP_STUN_IP:
      g_free (self->priv->stun_ip);
      self->priv->stun_ip = g_value_dup_string (value);
      break;
    case PROP_STUN_PORT:
      self->priv->stun_port = g_value_get_uint (value);
      break;
    case PROP_STUN_TIMEOUT:
      self->priv->stun_timeout = g_value_get_uint (value);
      break;
#ifdef HAVE_GUPNP
    case PROP_UPNP_MAPPING:
      self->priv->upnp_mapping = g_value_get_boolean (value);
      break;
    case PROP_UPNP_DISCOVERY:
      self->priv->upnp_discovery = g_value_get_boolean (value);
      break;
    case PROP_UPNP_MAPPING_TIMEOUT:
      self->priv->upnp_mapping_timeout = g_value_get_uint (value);
      break;
    case PROP_UPNP_DISCOVERY_TIMEOUT:
      self->priv->upnp_discovery_timeout = g_value_get_uint (value);
      break;
#else
    case PROP_UPNP_MAPPING:
    case PROP_UPNP_DISCOVERY:
    case PROP_UPNP_MAPPING_TIMEOUT:
    case PROP_UPNP_DISCOVERY_TIMEOUT:
      break;
#endif
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
