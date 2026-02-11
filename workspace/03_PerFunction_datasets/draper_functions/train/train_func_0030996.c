setup_source (GstURIDecodeBin * decoder)
{
  gboolean is_raw, have_out, is_dynamic;

  GST_DEBUG_OBJECT (decoder, "setup source");


  remove_source (decoder);

  decoder->pending = 0;


  if (!(decoder->source = gen_source_element (decoder)))
    goto no_source;


  gst_bin_add (GST_BIN_CAST (decoder), decoder->source);


  g_object_notify (G_OBJECT (decoder), "source");

  g_signal_emit (decoder, gst_uri_decode_bin_signals[SIGNAL_SOURCE_SETUP],
      0, decoder->source);


  remove_decoders (decoder, FALSE);


  decoder->streams = g_hash_table_new_full (NULL, NULL, NULL, free_stream);


  if (!analyse_source (decoder, &is_raw, &have_out, &is_dynamic,
          decoder->need_queue))
    goto invalid_source;

  if (is_raw) {
    GST_DEBUG_OBJECT (decoder, "Source provides all raw data");


    gst_element_no_more_pads (GST_ELEMENT_CAST (decoder));
    return TRUE;
  }
  if (!have_out && !is_dynamic) {
    GST_DEBUG_OBJECT (decoder, "Source has no output pads");


    add_element_stream (decoder->source, decoder);
    return TRUE;
  }
  if (is_dynamic) {
    GST_DEBUG_OBJECT (decoder, "Source has dynamic output pads");

    decoder->src_np_sig_id =
        g_signal_connect (decoder->source, "pad-added",
        G_CALLBACK (source_new_pad), decoder);
    decoder->src_nmp_sig_id =
        g_signal_connect (decoder->source, "no-more-pads",
        G_CALLBACK (source_no_more_pads), decoder);
    g_object_set_data (G_OBJECT (decoder->source), "pending",
        GINT_TO_POINTER (1));
    decoder->pending++;
  } else {
    if (decoder->is_stream) {
      GST_DEBUG_OBJECT (decoder, "Setting up streaming");

      if (!setup_streaming (decoder))
        goto streaming_failed;
    } else {
      GstElement *dec_elem;


      GST_DEBUG_OBJECT (decoder, "Plugging decodebin to source");

      dec_elem = make_decoder (decoder);
      if (!dec_elem)
        goto no_decoder;

      if (!gst_element_link_pads (decoder->source, NULL, dec_elem, "sink"))
        goto could_not_link;
    }
  }
  return TRUE;


no_source:
  {

    return FALSE;
  }
invalid_source:
  {
    GST_ELEMENT_ERROR (decoder, CORE, FAILED,
        (_("Source element is invalid.")), (NULL));
    return FALSE;
  }
no_decoder:
  {

    return FALSE;
  }
streaming_failed:
  {

    return FALSE;
  }
could_not_link:
  {
    GST_ELEMENT_ERROR (decoder, CORE, NEGOTIATION,
        (NULL), ("Can't link source to decoder element"));
    return FALSE;
  }
}
