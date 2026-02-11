gst_audio_encoder_set_headers (GstAudioEncoder * enc, GList * headers)
{
  GST_DEBUG_OBJECT (enc, "new headers %p", headers);

  if (enc->priv->ctx.headers) {
    g_list_foreach (enc->priv->ctx.headers, (GFunc) gst_buffer_unref, NULL);
    g_list_free (enc->priv->ctx.headers);
  }
  enc->priv->ctx.headers = headers;
  enc->priv->ctx.new_headers = TRUE;
}
