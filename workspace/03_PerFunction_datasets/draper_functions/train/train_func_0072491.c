gst_test_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstTest *test = GST_TEST (object);

  if (prop_id == 0 || prop_id > 2 * TESTS_COUNT) {
    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
    return;
  }

  if (prop_id % 2) {

    G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
  } else {

    GST_OBJECT_LOCK (test);
    g_value_copy (value, &test->values[prop_id / 2 - 1]);
    GST_OBJECT_UNLOCK (test);
  }
}
