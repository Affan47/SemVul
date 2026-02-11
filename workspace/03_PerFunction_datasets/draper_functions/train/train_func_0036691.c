_get_decoder_factories (gpointer arg)
{
  GstElementClass *klass = arg;
  GList *factories;
  GstPadTemplate *templ = gst_element_class_get_pad_template (klass,
      "sink");
  RsnDecFactoryFilterCtx ctx = { NULL, };
  GstCaps *raw;
  gboolean raw_audio;

  ctx.desired_caps = gst_pad_template_get_caps (templ);

  raw = gst_caps_from_string ("audio/x-raw-float");
  raw_audio = gst_caps_can_intersect (raw, ctx.desired_caps);
  if (raw_audio) {
    GstCaps *sub = gst_caps_subtract (ctx.desired_caps, raw);
    ctx.desired_caps = sub;
  } else {
    gst_caps_ref (ctx.desired_caps);
  }
  gst_caps_unref (raw);


  ctx.decoder_caps = gst_caps_new_empty ();
  GST_DEBUG ("Finding factories for caps: %" GST_PTR_FORMAT, ctx.desired_caps);

  factories = gst_default_registry_feature_filter (
      (GstPluginFeatureFilter) rsndec_factory_filter, FALSE, &ctx);


  if (raw_audio) {
    GstPluginFeature *feature;
    GST_DEBUG ("These are audio caps, adding audioconvert");
    feature =
        gst_default_registry_find_feature ("audioconvert",
        GST_TYPE_ELEMENT_FACTORY);
    if (feature) {
      factories = g_list_append (factories, feature);
    } else {
      GST_WARNING ("Could not find feature audioconvert");
    }
  }

  factories = g_list_sort (factories, (GCompareFunc) sort_by_ranks);

  GST_DEBUG ("Available decoder caps %" GST_PTR_FORMAT, ctx.decoder_caps);
  gst_caps_unref (ctx.decoder_caps);
  gst_caps_unref (ctx.desired_caps);

  return factories;
}
