gst_test_sink_event (GstBaseSink * basesink, GstEvent * event)
{
  GstTestClass *klass = GST_TEST_GET_CLASS (basesink);
  GstTest *test = GST_TEST (basesink);

  switch (GST_EVENT_TYPE (event)) {


    case GST_EVENT_EOS:{
      gint i;

      g_object_freeze_notify (G_OBJECT (test));
      for (i = 0; i < TESTS_COUNT; i++) {
        if (test->tests[i]) {
          if (!tests[i].finish (test->tests[i], &test->values[i])) {
            GValue v = { 0, };
            gchar *real, *expected;

            expected = gst_value_serialize (&test->values[i]);
            g_value_init (&v, G_VALUE_TYPE (&test->values[i]));
            g_object_get_property (G_OBJECT (test), klass->param_names[2 * i],
                &v);
            real = gst_value_serialize (&v);
            g_value_unset (&v);
            GST_ELEMENT_ERROR (test, STREAM, FORMAT, (NULL),
                ("test %s returned value \"%s\" and not expected value \"%s\"",
                    klass->param_names[2 * i], real, expected));
            g_free (real);
            g_free (expected);
          }
          g_object_notify (G_OBJECT (test), klass->param_names[2 * i]);
        }
      }
      g_object_thaw_notify (G_OBJECT (test));
      break;
    }
    default:
      break;
  }

  return GST_BASE_SINK_CLASS (parent_class)->event (basesink, event);
}
