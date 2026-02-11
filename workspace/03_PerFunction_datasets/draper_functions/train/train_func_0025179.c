gst_ogg_mux_sinkconnect (GstPad * pad, GstObject * parent, GstPad * peer)
{
  GstOggMux *ogg_mux;

  ogg_mux = GST_OGG_MUX (parent);

  GST_DEBUG_OBJECT (ogg_mux, "sinkconnect triggered on %s", GST_PAD_NAME (pad));

  return GST_PAD_LINK_OK;
}
