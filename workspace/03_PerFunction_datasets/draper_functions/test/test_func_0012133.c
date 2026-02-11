mpegvideoparse_drain_avail (MpegVideoParse * mpegvideoparse)
{
  MPEGBlockInfo *cur;
  GstBuffer *buf = NULL;
  GstFlowReturn res = GST_FLOW_OK;

  cur = mpeg_packetiser_get_block (&mpegvideoparse->packer, &buf);
  while ((cur != NULL) && (res == GST_FLOW_OK)) {

    GST_LOG_OBJECT (mpegvideoparse,
        "Have block of size %u with pack_type %s and flags 0x%02x",
        cur->length, picture_start_code_name (cur->first_pack_type),
        cur->flags);

    if ((cur->flags & MPEG_BLOCK_FLAG_SEQUENCE) && buf != NULL) {

      if (!mpegvideoparse_handle_sequence (mpegvideoparse, buf)) {
        GST_DEBUG_OBJECT (mpegvideoparse,
            "Invalid sequence header. Dropping buffer.");
        gst_buffer_unref (buf);
        buf = NULL;
      }
    } else if (mpegvideoparse->seq_hdr.mpeg_version == 0 && buf) {

      GST_DEBUG_OBJECT (mpegvideoparse,
          "No sequence header yet. Dropping buffer of %u bytes",
          GST_BUFFER_SIZE (buf));
      gst_buffer_unref (buf);
      buf = NULL;
    }

    if (buf != NULL) {


      if (cur->flags & MPEG_BLOCK_FLAG_PICTURE) {
        if (!mpegvideoparse_handle_picture (mpegvideoparse, buf)) {

          GST_DEBUG_OBJECT (mpegvideoparse,
              "Corrupted picture header. Dropping buffer of %u bytes",
              GST_BUFFER_SIZE (buf));
          mpegvideoparse->need_discont = TRUE;
          gst_buffer_unref (buf);
          buf = NULL;
        }
      }
    }

    if (buf != NULL) {
      GST_DEBUG_OBJECT (mpegvideoparse,
          "mpegvideoparse: pushing buffer of %u bytes with ts %"
          GST_TIME_FORMAT, GST_BUFFER_SIZE (buf),
          GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (buf)));

      gst_buffer_set_caps (buf, GST_PAD_CAPS (mpegvideoparse->srcpad));

      if (mpegvideoparse->need_discont) {
        GST_DEBUG_OBJECT (mpegvideoparse,
            "setting discont flag on outgoing buffer");
        GST_BUFFER_FLAG_SET (buf, GST_BUFFER_FLAG_DISCONT);
        mpegvideoparse->need_discont = FALSE;
      }

      mpv_send_pending_segs (mpegvideoparse);

      res = gst_pad_push (mpegvideoparse->srcpad, buf);
      buf = NULL;
    }


    mpeg_packetiser_next_block (&mpegvideoparse->packer);
    cur = mpeg_packetiser_get_block (&mpegvideoparse->packer, &buf);
  }
  if (buf != NULL)
    gst_buffer_unref (buf);

  return res;
}
