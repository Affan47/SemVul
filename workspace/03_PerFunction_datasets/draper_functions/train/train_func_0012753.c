gst_zebra_stripe_set_property (GObject * object, guint property_id,
    const GValue * value, GParamSpec * pspec)
{
  GstZebraStripe *zebrastripe = GST_ZEBRA_STRIPE (object);

  GST_DEBUG_OBJECT (zebrastripe, "set_property");

  switch (property_id) {
    case PROP_THRESHOLD:
      zebrastripe->threshold = g_value_get_int (value);
      zebrastripe->y_threshold =
          16 + floor (0.5 + 2.19 * zebrastripe->threshold);
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, property_id, pspec);
      break;
  }
}
