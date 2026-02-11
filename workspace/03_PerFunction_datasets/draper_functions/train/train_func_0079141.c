gst_rtp_vp8_pay_init (GstRtpVP8Pay * obj, GstRtpVP8PayClass * klass)
{

  obj->picture_id_mode = DEFAULT_PICTURE_ID_MODE;
  if (obj->picture_id_mode == VP8_PAY_PICTURE_ID_7BITS)
    obj->picture_id = g_random_int_range (0, G_MAXUINT8) & 0x7F;
  else if (obj->picture_id_mode == VP8_PAY_PICTURE_ID_15BITS)
    obj->picture_id = g_random_int_range (0, G_MAXUINT16) & 0x7FFF;
}
