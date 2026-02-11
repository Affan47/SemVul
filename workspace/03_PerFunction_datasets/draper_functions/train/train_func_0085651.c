gst_tag_mux_init (GstTagMux * mux, GstTagMuxClass * mux_class)
{
  GstElementClass *element_klass = GST_ELEMENT_CLASS (mux_class);
  GstPadTemplate *tmpl;

  mux->priv =
      G_TYPE_INSTANCE_GET_PRIVATE (mux, GST_TYPE_TAG_MUX, GstTagMuxPrivate);


  tmpl = gst_element_class_get_pad_template (element_klass, "sink");
  if (tmpl) {
    mux->priv->sinkpad = gst_pad_new_from_template (tmpl, "sink");
  } else {
    g_warning ("GstTagMux subclass '%s' did not install a %s pad template!\n",
        G_OBJECT_CLASS_NAME (mux_class), "sink");
    mux->priv->sinkpad = gst_pad_new ("sink", GST_PAD_SINK);
  }
  gst_pad_set_chain_function (mux->priv->sinkpad,
      GST_DEBUG_FUNCPTR (gst_tag_mux_chain));
  gst_pad_set_event_function (mux->priv->sinkpad,
      GST_DEBUG_FUNCPTR (gst_tag_mux_sink_event));
  gst_element_add_pad (GST_ELEMENT (mux), mux->priv->sinkpad);


  tmpl = gst_element_class_get_pad_template (element_klass, "src");
  if (tmpl) {
    GstCaps *tmpl_caps = gst_pad_template_get_caps (tmpl);

    mux->priv->srcpad = gst_pad_new_from_template (tmpl, "src");
    gst_pad_use_fixed_caps (mux->priv->srcpad);
    if (tmpl_caps != NULL && gst_caps_is_fixed (tmpl_caps)) {
      gst_pad_set_caps (mux->priv->srcpad, tmpl_caps);
    }
  } else {
    g_warning ("GstTagMux subclass '%s' did not install a %s pad template!\n",
        G_OBJECT_CLASS_NAME (mux_class), "source");
    mux->priv->srcpad = gst_pad_new ("src", GST_PAD_SRC);
  }
  gst_element_add_pad (GST_ELEMENT (mux), mux->priv->srcpad);

  mux->priv->render_start_tag = TRUE;
  mux->priv->render_end_tag = TRUE;
}
