gst_basertppayload_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstBaseRTPPayload *basertppayload;
  GstBaseRTPPayloadPrivate *priv;
  gint64 val;

  basertppayload = GST_BASE_RTP_PAYLOAD (object);
  priv = basertppayload->priv;

  switch (prop_id) {
    case PROP_MTU:
      basertppayload->mtu = g_value_get_uint (value);
      break;
    case PROP_PT:
      basertppayload->pt = g_value_get_uint (value);
      break;
    case PROP_SSRC:
      val = g_value_get_uint (value);
      basertppayload->ssrc = val;
      priv->ssrc_random = FALSE;
      break;
    case PROP_TIMESTAMP_OFFSET:
      val = g_value_get_uint (value);
      basertppayload->ts_offset = val;
      priv->ts_offset_random = FALSE;
      break;
    case PROP_SEQNUM_OFFSET:
      val = g_value_get_int (value);
      basertppayload->seqnum_offset = val;
      priv->seqnum_offset_random = (val == -1);
      GST_DEBUG_OBJECT (basertppayload, "seqnum offset 0x%04x, random %d",
          basertppayload->seqnum_offset, priv->seqnum_offset_random);
      break;
    case PROP_MAX_PTIME:
      basertppayload->priv->prop_max_ptime = g_value_get_int64 (value);
      update_max_ptime (basertppayload);
      break;
    case PROP_MIN_PTIME:
      basertppayload->min_ptime = g_value_get_int64 (value);
      break;
    case PROP_PERFECT_RTPTIME:
      priv->perfect_rtptime = g_value_get_boolean (value);
      break;
    case PROP_PTIME_MULTIPLE:
      basertppayload->abidata.ABI.ptime_multiple = g_value_get_int64 (value);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
