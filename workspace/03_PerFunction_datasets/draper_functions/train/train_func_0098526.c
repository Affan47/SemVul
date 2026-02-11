gst_discoverer_set_timeout (GstDiscoverer * dc, GstClockTime timeout)
{
  GST_DEBUG_OBJECT (dc, "timeout : %" GST_TIME_FORMAT, GST_TIME_ARGS (timeout));


  DISCO_LOCK (dc);
  dc->priv->timeout = timeout;
  DISCO_UNLOCK (dc);
}
