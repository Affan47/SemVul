theora_dec_chain (GstPad * pad, GstBuffer * buf)
{
  GstTheoraDec *dec;
  GstFlowReturn res;
  gboolean discont;

  dec = GST_THEORA_DEC (gst_pad_get_parent (pad));


  discont = GST_BUFFER_IS_DISCONT (buf);


  if (G_UNLIKELY (discont)) {
    GST_DEBUG_OBJECT (dec, "received DISCONT buffer");
    dec->need_keyframe = TRUE;
    dec->last_timestamp = -1;
    dec->discont = TRUE;
  }

  if (dec->segment.rate > 0.0)
    res = theora_dec_chain_forward (dec, discont, buf);
  else
    res = theora_dec_chain_reverse (dec, discont, buf);

  gst_object_unref (dec);

  return res;
}
