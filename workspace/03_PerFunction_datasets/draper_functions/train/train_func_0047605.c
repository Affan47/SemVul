gst_mve_demux_chain (GstPad * sinkpad, GstBuffer * inbuf)
{
  GstMveDemux *mve = GST_MVE_DEMUX (GST_PAD_PARENT (sinkpad));
  GstFlowReturn ret = GST_FLOW_OK;

  gst_adapter_push (mve->adapter, inbuf);

  GST_DEBUG_OBJECT (mve, "queuing buffer, needed:%d, available:%u",
      mve->needed_bytes, gst_adapter_available (mve->adapter));

  while ((gst_adapter_available (mve->adapter) >= mve->needed_bytes) &&
      (ret == GST_FLOW_OK)) {
    GstMveDemuxStream *stream = NULL;
    GstBuffer *outbuf = NULL;

    switch (mve->state) {
      case MVEDEMUX_STATE_INITIAL:
        gst_adapter_flush (mve->adapter, mve->needed_bytes);

        mve->chunk_offset += mve->needed_bytes;
        mve->needed_bytes = 4;
        mve->state = MVEDEMUX_STATE_NEXT_CHUNK;
        break;

      case MVEDEMUX_STATE_NEXT_CHUNK:{
        const guint8 *data;
        guint16 size;

        data = gst_adapter_peek (mve->adapter, mve->needed_bytes);
        size = GST_MVE_SEGMENT_SIZE (data);

        if (mve->chunk_offset >= mve->chunk_size) {

          guint16 chunk_type = GST_READ_UINT16_LE (data + 2);

          gst_adapter_flush (mve->adapter, mve->needed_bytes);
          mve->chunk_size = size;
          mve->chunk_offset = 0;

          if (chunk_type > MVE_CHUNK_END) {
            GST_WARNING_OBJECT (mve,
                "skipping unknown chunk type 0x%02x of size:%u", chunk_type,
                size);
            mve->needed_bytes += size;
            mve->state = MVEDEMUX_STATE_SKIP;
          } else {
            GST_DEBUG_OBJECT (mve, "found new chunk type 0x%02x of size:%u",
                chunk_type, size);
          }
        } else if (mve->chunk_offset <= mve->chunk_size) {

          GST_DEBUG_OBJECT (mve, "found segment type 0x%02x of size:%u",
              GST_MVE_SEGMENT_TYPE (data), size);

          mve->needed_bytes += size;
          mve->state = MVEDEMUX_STATE_MOVIE;
        }
      }
        break;

      case MVEDEMUX_STATE_MOVIE:
        ret = gst_mve_parse_segment (mve, &stream, &outbuf);

        if ((ret == GST_FLOW_OK) && (outbuf != NULL)) {

          GST_DEBUG_OBJECT (mve,
              "pushing buffer with time %" GST_TIME_FORMAT
              " (%u bytes) on pad %s",
              GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (outbuf)),
              GST_BUFFER_SIZE (outbuf), GST_PAD_NAME (stream->pad));

          ret = gst_pad_push (stream->pad, outbuf);
          stream->last_flow = ret;
        }

        if (ret == GST_FLOW_NOT_LINKED) {
          if (mve->audio_stream
              && mve->audio_stream->last_flow != GST_FLOW_NOT_LINKED)
            ret = GST_FLOW_OK;
          if (mve->video_stream
              && mve->video_stream->last_flow != GST_FLOW_NOT_LINKED)
            ret = GST_FLOW_OK;
        }


        mve->chunk_offset += mve->needed_bytes;

        mve->state = MVEDEMUX_STATE_NEXT_CHUNK;
        mve->needed_bytes = 4;
        break;

      case MVEDEMUX_STATE_SKIP:
        mve->chunk_offset += mve->needed_bytes;
        gst_adapter_flush (mve->adapter, mve->needed_bytes);
        mve->state = MVEDEMUX_STATE_NEXT_CHUNK;
        mve->needed_bytes = 4;
        break;

      default:
        GST_ERROR_OBJECT (mve, "invalid state: %d", mve->state);
        break;
    }
  }

  return ret;
}
