rfb_decoder_new (void)
{
  RfbDecoder *decoder = g_new0 (RfbDecoder, 1);

  decoder->socket = NULL;
  decoder->cancellable = g_cancellable_new ();

  decoder->password = NULL;

  decoder->use_copyrect = FALSE;

  decoder->offset_x = 0;
  decoder->offset_y = 0;
  decoder->rect_width = 0;
  decoder->rect_height = 0;
  decoder->shared_flag = TRUE;
  decoder->disconnected = FALSE;
  decoder->data = NULL;
  decoder->data_len = 0;
  decoder->error = NULL;

  return decoder;
}
