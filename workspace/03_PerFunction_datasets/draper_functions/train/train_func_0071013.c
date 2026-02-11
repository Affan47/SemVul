rsndec_factory_filter (GstPluginFeature * feature, RsnDecFactoryFilterCtx * ctx)
{
  GstElementFactory *factory;
  guint rank;
  const gchar *klass;
  const GList *templates;
  GList *walk;
  gboolean can_sink = FALSE;


  if (!GST_IS_ELEMENT_FACTORY (feature))
    return FALSE;

  factory = GST_ELEMENT_FACTORY (feature);

  klass =
      gst_element_factory_get_metadata (factory, GST_ELEMENT_METADATA_KLASS);

  if (strstr (klass, "Decoder") == NULL)
    return FALSE;


  rank = gst_plugin_feature_get_rank (feature);
  if (rank < GST_RANK_MARGINAL)
    return FALSE;


  templates = gst_element_factory_get_static_pad_templates (factory);
  for (walk = (GList *) templates; walk && !can_sink; walk = g_list_next (walk)) {
    GstStaticPadTemplate *templ = walk->data;


    if (templ->direction == GST_PAD_SINK) {
      GstCaps *intersect;
      GstCaps *tmpl_caps;


      tmpl_caps = gst_static_caps_get (&templ->static_caps);

      intersect = gst_caps_intersect (ctx->desired_caps, tmpl_caps);
      gst_caps_unref (tmpl_caps);


      if (!gst_caps_is_empty (intersect)) {

        can_sink = TRUE;
        ctx->decoder_caps = gst_caps_merge (ctx->decoder_caps, intersect);
      } else
        gst_caps_unref (intersect);
    }
  }

  if (can_sink) {
    GST_DEBUG ("Found decoder element %s (%s)",
        gst_element_factory_get_metadata (factory,
            GST_ELEMENT_METADATA_LONGNAME),
        gst_plugin_feature_get_name (feature));
  }

  return can_sink;
}
