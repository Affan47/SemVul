user_end_callback (png_structp png_ptr, png_infop info)
{
  GstPngDec *pngdec = NULL;

  pngdec = GST_PNGDEC (png_get_io_ptr (png_ptr));

  GST_LOG_OBJECT (pngdec, "and we are done reading this image");

  if (!pngdec->buffer_out)
    return;

  if (GST_CLOCK_TIME_IS_VALID (pngdec->in_timestamp))
    GST_BUFFER_TIMESTAMP (pngdec->buffer_out) = pngdec->in_timestamp;
  if (GST_CLOCK_TIME_IS_VALID (pngdec->in_duration))
    GST_BUFFER_DURATION (pngdec->buffer_out) = pngdec->in_duration;


  if (buffer_clip (pngdec, pngdec->buffer_out)) {

    GST_LOG_OBJECT (pngdec, "pushing buffer with ts=%" GST_TIME_FORMAT,
        GST_TIME_ARGS (GST_BUFFER_TIMESTAMP (pngdec->buffer_out)));

    pngdec->ret = gst_pad_push (pngdec->srcpad, pngdec->buffer_out);
  } else {
    GST_LOG_OBJECT (pngdec, "dropped decoded buffer");
    gst_buffer_unref (pngdec->buffer_out);
  }
  pngdec->buffer_out = NULL;
  pngdec->image_ready = TRUE;
}
