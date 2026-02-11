gst_schro_dec_process (GstSchroDec * schro_dec, gboolean eos)
{
  gboolean go;
  GstFlowReturn ret;

  ret = GST_FLOW_OK;
  go = TRUE;
  while (go) {
    int it;

    it = schro_decoder_autoparse_wait (schro_dec->decoder);

    switch (it) {
      case SCHRO_DECODER_FIRST_ACCESS_UNIT:
        break;
      case SCHRO_DECODER_NEED_BITS:
        GST_DEBUG ("need bits");
        go = 0;
        break;
      case SCHRO_DECODER_NEED_FRAME:
      {
        GstBuffer *outbuf;
        GstVideoCodecState *state;
        SchroFrame *schro_frame;

        GST_DEBUG ("need frame");

        state =
            gst_video_decoder_get_output_state (GST_VIDEO_DECODER (schro_dec));
        outbuf =
            gst_video_decoder_allocate_output_buffer (GST_VIDEO_DECODER
            (schro_dec));
        schro_frame = gst_schro_buffer_wrap (outbuf, TRUE, &state->info);
        schro_decoder_add_output_picture (schro_dec->decoder, schro_frame);
        gst_video_codec_state_unref (state);
        break;
      }
      case SCHRO_DECODER_OK:
      {
        SchroFrame *schro_frame;
        SchroTag *tag;
        GstVideoCodecFrame *frame;

        GST_DEBUG ("got frame");

        tag = schro_decoder_get_picture_tag (schro_dec->decoder);
        schro_frame = schro_decoder_pull (schro_dec->decoder);
        frame = tag->value;

        if (schro_frame) {
          if ((frame->output_buffer = gst_schro_frame_get_buffer (schro_frame))) {
            GstFlowReturn flow_ret;

            flow_ret =
                gst_video_decoder_finish_frame (GST_VIDEO_DECODER
                (schro_dec), frame);
            if (flow_ret != GST_FLOW_OK) {
              GST_DEBUG ("finish frame returned %d", flow_ret);
              return flow_ret;
            }
          } else {
            GST_DEBUG ("skipped frame");
          }

          schro_frame_unref (schro_frame);
        }
        if (tag)
          schro_tag_free (tag);
        if (!eos) {
          go = FALSE;
        }
      }

        break;
      case SCHRO_DECODER_EOS:
        GST_DEBUG ("eos");
        go = FALSE;
        break;
      case SCHRO_DECODER_ERROR:
        go = FALSE;
        GST_DEBUG ("codec error");
        ret = GST_FLOW_ERROR;
        break;
      default:
        break;
    }
  }
  return ret;
}
