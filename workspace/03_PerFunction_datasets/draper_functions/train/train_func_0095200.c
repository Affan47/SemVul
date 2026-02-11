theora_parse_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstTheoraParse *parse = GST_THEORA_PARSE (object);

  switch (prop_id) {
    case PROP_SYNCHRONIZATION_POINTS:
    {
      GValueArray *array;
      guint i;

      array = g_value_get_boxed (value);

      if (array) {
        if (array->n_values % 2)
          goto odd_values;

        g_free (parse->times);
        parse->times = g_new (GstClockTime, array->n_values);
        parse->npairs = array->n_values / 2;
        for (i = 0; i < array->n_values; i++)
          parse->times[i] = g_value_get_uint64 (&array->values[i]);
      } else {
        g_free (parse->times);
        parse->npairs = 0;
      }
    }
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }

  return;

odd_values:
  {
    g_critical ("expected an even number of time values for "
        "synchronization-points");
    return;
  }
}
