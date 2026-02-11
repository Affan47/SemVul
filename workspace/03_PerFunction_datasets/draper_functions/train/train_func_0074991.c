theora_dec_start (GstVideoDecoder * decoder)
{
  GstTheoraDec *dec = GST_THEORA_DEC (decoder);

  GST_DEBUG_OBJECT (dec, "start");
  GST_DEBUG_OBJECT (dec, "Setting have_header to FALSE");
  dec->have_header = FALSE;
  dec->can_crop = FALSE;

  return TRUE;
}
