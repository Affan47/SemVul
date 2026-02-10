rfb_decoder_state_wait_for_security (RfbDecoder * decoder)
{


  if (IS_VERSION_3_3 (decoder)) {
    rfb_decoder_read (decoder, 4);

    decoder->security_type = RFB_GET_UINT32 (decoder->data);
    GST_DEBUG ("security = %d", decoder->security_type);

    g_return_val_if_fail (decoder->security_type < 3, FALSE);
    g_return_val_if_fail (decoder->security_type != SECURITY_FAIL,
        rfb_decoder_state_reason (decoder));
  } else {

    GST_WARNING ("Other versions are not yet supported");
  }

  switch (decoder->security_type) {
    case SECURITY_NONE:
      GST_DEBUG ("Security type is None");
      if (IS_VERSION_3_8 (decoder)) {
        decoder->state = rfb_decoder_state_security_result;
      } else {
        decoder->state = rfb_decoder_state_send_client_initialisation;
      }
      break;
    case SECURITY_VNC:


      GST_DEBUG ("Security type is VNC Authentication");

      if (!decoder->password) {
        GST_WARNING
            ("VNC Authentication can't be used if the password is not set");
        return FALSE;
      }

      rfb_decoder_read (decoder, 16);
      vncEncryptBytes ((unsigned char *) decoder->data, decoder->password);
      rfb_decoder_send (decoder, decoder->data, 16);

      GST_DEBUG ("Encrypted challenge send to server");

      decoder->state = rfb_decoder_state_security_result;
      break;
    default:
      GST_WARNING ("Security type is not known");
      return FALSE;
      break;
  }
  return TRUE;
}
