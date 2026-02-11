gst_mfc_dec_flush (GstVideoDecoder * decoder)
{
  GstMFCDec *self = GST_MFC_DEC (decoder);

  GST_DEBUG_OBJECT (self, "Flushing");
  if (self->context)
    mfc_dec_flush (self->context);

  return TRUE;
}
