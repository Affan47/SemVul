gst_flups_demux_parse_psm (GstFluPSDemux * demux)
{
  guint16 length = 0, info_length = 0, es_map_length = 0;
  guint8 psm_version = 0;
  const guint8 *data, *es_map_base;
  gboolean applicable;


  if (!(data = gst_adapter_peek (demux->adapter, 6)))
    goto need_more_data;


  data += 4;

  length = GST_READ_UINT16_BE (data);
  GST_DEBUG_OBJECT (demux, "length %u", length);

  if (G_UNLIKELY (length > 0x3FA))
    goto psm_len_error;

  length += 6;

  if (!(data = gst_adapter_peek (demux->adapter, length)))
    goto need_more_data;


  data += 6;


  psm_version = GST_READ_UINT8 (data);
  applicable = (psm_version & 0x80) >> 7;
  psm_version &= 0x1F;
  GST_DEBUG_OBJECT (demux, "PSM version %u (applicable now %u)", psm_version,
      applicable);


  data += 2;


  info_length = GST_READ_UINT16_BE (data);

  info_length = MIN (length - 16, info_length);
  GST_DEBUG_OBJECT (demux, "PS info length %u bytes", info_length);


  data += (2 + info_length);


  es_map_length = GST_READ_UINT16_BE (data);

  es_map_length = MIN (length - (16 + info_length), es_map_length);
  GST_DEBUG_OBJECT (demux, "ES map length %u bytes", es_map_length);


  data += 2;


  es_map_base = data;
  while (es_map_base + 4 <= data + es_map_length) {
    guint8 stream_type = 0, stream_id = 0;
    guint16 stream_info_length = 0;

    stream_type = GST_READ_UINT8 (es_map_base);
    es_map_base++;
    stream_id = GST_READ_UINT8 (es_map_base);
    es_map_base++;
    stream_info_length = GST_READ_UINT16_BE (es_map_base);
    es_map_base += 2;

    stream_info_length = MIN (data + es_map_length - es_map_base,
        stream_info_length);

    GST_DEBUG_OBJECT (demux, "Stream type %02X with id %02X and %u bytes info",
        stream_type, stream_id, stream_info_length);
    demux->psm[stream_id] = stream_type;
    es_map_base += stream_info_length;
  }

  gst_adapter_flush (demux->adapter, length);
  ADAPTER_OFFSET_FLUSH (length);
  return GST_FLOW_OK;

psm_len_error:
  {
    GST_DEBUG_OBJECT (demux, "error in PSM length");
    return GST_FLOW_LOST_SYNC;
  }
need_more_data:
  {
    GST_DEBUG_OBJECT (demux, "need more data");
    return GST_FLOW_NEED_MORE_DATA;
  }
}
