gst_pnmdec_chain_raw (GstPnmdec * s, GstPad * src, GstBuffer * buf)
{
  GstFlowReturn r = GST_FLOW_OK;
  GstBuffer *out;


  if (gst_buffer_get_size (buf) == s->size) {
    memset (&s->mngr, 0, sizeof (GstPnmInfoMngr));
    s->size = 0;
    return gst_pnmdec_push (s, src, buf);
  }


  if (!s->buf) {
    s->buf = buf;
  } else {
    out = gst_buffer_append (s->buf, buf);
    s->buf = out;
  }
  if (!s->buf)
    return GST_FLOW_ERROR;


  if (gst_buffer_get_size (s->buf) == s->size) {
    r = gst_pnmdec_push (s, src, s->buf);
    s->buf = NULL;
    memset (&s->mngr, 0, sizeof (GstPnmInfoMngr));
    s->size = 0;
  }

  return r;
}
