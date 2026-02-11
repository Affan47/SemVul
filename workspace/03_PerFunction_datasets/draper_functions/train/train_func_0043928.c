rfb_decoder_state_security_result (RfbDecoder * decoder)
{
  rfb_decoder_read (decoder, 4);
  if (RFB_GET_UINT32 (decoder->data) != 0) {
    GST_WARNING ("Security handshaking failed");
    if (IS_VERSION_3_8 (decoder)) {
      decoder->state = rfb_decoder_state_reason;
      return TRUE;
    }
    return FALSE;
  }

  GST_DEBUG ("Security handshaking succesfull");
  decoder->state = rfb_decoder_state_send_client_initialisation;

  return TRUE;
}
