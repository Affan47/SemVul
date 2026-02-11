update_ltr (GstUvcH264Src * self)
{
  uvcx_ltr_buffer_size_control_t req;

  if (!xu_query (self, UVCX_LTR_BUFFER_SIZE_CONTROL, UVC_GET_CUR,
          (guchar *) & req)) {
    GST_WARNING_OBJECT (self, " LTR_BUFFER_SIZE GET_CUR error");
    return;
  }

  if (self->ltr_buffer_size != req.bLTRBufferSize) {
    self->ltr_buffer_size = req.bLTRBufferSize;
    g_object_notify (G_OBJECT (self), "ltr-buffer-size");
  }
  if (self->ltr_encoder_control != req.bLTREncoderControl) {
    self->ltr_encoder_control = req.bLTREncoderControl;
    g_object_notify (G_OBJECT (self), "ltr-encoder-control");
  }
}
