gst_mve_parse_segment (GstMveDemux * mve, GstMveDemuxStream ** stream,
    GstBuffer ** send)
{
  GstFlowReturn ret = GST_FLOW_OK;
  const guint8 *buffer, *data;
  guint8 type, version;
  guint16 len;

  buffer = gst_adapter_peek (mve->adapter, mve->needed_bytes);

  type = GST_MVE_SEGMENT_TYPE (buffer);


  if (type < 32) {
    version = GST_MVE_SEGMENT_VERSION (buffer);
    len = GST_MVE_SEGMENT_SIZE (buffer);
    data = buffer + 4;

    switch (type) {

      case MVE_OC_END_OF_CHUNK:
        gst_mve_end_chunk (mve);
        break;
      case MVE_OC_CREATE_TIMER:
        ret = gst_mve_timer_create (mve, data, len, send);
        *stream = mve->audio_stream;
        break;
      case MVE_OC_AUDIO_BUFFERS:
        ret = gst_mve_audio_init (mve, version, data, len);
        break;
      case MVE_OC_VIDEO_BUFFERS:
        ret = gst_mve_video_create_buffer (mve, version, data, len);
        break;
      case MVE_OC_AUDIO_DATA:
      case MVE_OC_AUDIO_SILENCE:
        ret = gst_mve_audio_data (mve, type, data, len, send);
        *stream = mve->audio_stream;
        break;
      case MVE_OC_VIDEO_MODE:
        ret = gst_mve_video_init (mve, data);
        break;
      case MVE_OC_PALETTE:
        ret = gst_mve_video_palette (mve, data, len);
        break;
      case MVE_OC_PALETTE_COMPRESSED:
        ret = gst_mve_video_palette_compressed (mve, data, len);
        break;
      case MVE_OC_CODE_MAP:
        ret = gst_mve_video_code_map (mve, data, len);
        break;
      case MVE_OC_VIDEO_DATA:
        ret = gst_mve_video_data (mve, data, len, send);
        *stream = mve->video_stream;
        break;

      case MVE_OC_END_OF_STREAM:
      case MVE_OC_PLAY_AUDIO:
      case MVE_OC_PLAY_VIDEO:

        GST_LOG_OBJECT (mve, "ignored segment type:0x%02x, version:0x%02x",
            type, version);
        break;
      case 0x13:
      case 0x14:
      case 0x15:

        GST_DEBUG_OBJECT (mve,
            "known but unhandled segment type:0x%02x, version:0x%02x", type,
            version);
        break;
      default:
        GST_WARNING_OBJECT (mve,
            "unhandled segment type:0x%02x, version:0x%02x", type, version);
        break;
    }
  }

  gst_adapter_flush (mve->adapter, mve->needed_bytes);
  return ret;
}
