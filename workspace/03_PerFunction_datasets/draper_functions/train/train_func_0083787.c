_gst_audio_decoder_error (GstAudioDecoder * dec, gint weight,
    GQuark domain, gint code, gchar * txt, gchar * dbg, const gchar * file,
    const gchar * function, gint line)
{
  if (txt)
    GST_WARNING_OBJECT (dec, "error: %s", txt);
  if (dbg)
    GST_WARNING_OBJECT (dec, "error: %s", dbg);
  dec->priv->error_count += weight;
  dec->priv->discont = TRUE;
  if (dec->priv->ctx.max_errors < dec->priv->error_count) {
    gst_element_message_full (GST_ELEMENT (dec), GST_MESSAGE_ERROR,
        domain, code, txt, dbg, file, function, line);
    return GST_FLOW_ERROR;
  } else {
    g_free (txt);
    g_free (dbg);
    return GST_FLOW_OK;
  }
}
