gst_cmml_enc_change_state (GstElement * element, GstStateChange transition)
{
  GstCmmlEnc *enc = GST_CMML_ENC (element);
  GstStateChangeReturn res;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      enc->parser = gst_cmml_parser_new (GST_CMML_PARSER_ENCODE);
      enc->parser->user_data = enc;
      enc->parser->preamble_callback =
          (GstCmmlParserPreambleCallback) gst_cmml_enc_parse_preamble;
      enc->parser->head_callback =
          (GstCmmlParserHeadCallback) gst_cmml_enc_parse_tag_head;
      enc->parser->clip_callback =
          (GstCmmlParserClipCallback) gst_cmml_enc_parse_tag_clip;
      enc->parser->cmml_end_callback =
          (GstCmmlParserCmmlEndCallback) gst_cmml_enc_parse_end_tag;
      enc->tracks = gst_cmml_track_list_new ();
      enc->sent_headers = FALSE;
      enc->sent_eos = FALSE;
      enc->flow_return = GST_FLOW_OK;
      break;
    default:
      break;
  }

  res = parent_class->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PAUSED_TO_READY:
    {
      gst_cmml_track_list_destroy (enc->tracks);
      enc->tracks = NULL;
      g_free (enc->preamble);
      enc->preamble = NULL;
      gst_cmml_parser_free (enc->parser);
      break;
    }
    default:
      break;
  }

  return res;
}
