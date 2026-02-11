gst_real_audio_demux_parse_marker (GstRealAudioDemux * demux)
{
  guint8 data[6];

  if (gst_adapter_available (demux->adapter) < 6) {
    GST_LOG_OBJECT (demux, "need at least 6 bytes, waiting for more data");
    return GST_FLOW_OK;
  }

  gst_adapter_copy (demux->adapter, data, 0, 6);
  if (memcmp (data, ".ra\375", 4) != 0)
    goto wrong_format;

  demux->ra_version = GST_READ_UINT16_BE (data + 4);
  GST_DEBUG_OBJECT (demux, "ra_version   = %u", demux->ra_version);
  if (demux->ra_version != 4 && demux->ra_version != 3)
    goto unsupported_ra_version;

  gst_adapter_flush (demux->adapter, 6);
  demux->state = REAL_AUDIO_DEMUX_STATE_HEADER;
  return GST_FLOW_OK;


wrong_format:
  {
    GST_ELEMENT_ERROR (GST_ELEMENT (demux), STREAM, WRONG_TYPE, (NULL), (NULL));
    return GST_FLOW_ERROR;
  }

unsupported_ra_version:
  {
    GST_ELEMENT_ERROR (GST_ELEMENT (demux), STREAM, DECODE,
        ("Cannot decode this RealAudio file, please file a bug"),
        ("ra_version = %u", demux->ra_version));
    return GST_FLOW_ERROR;
  }
}
