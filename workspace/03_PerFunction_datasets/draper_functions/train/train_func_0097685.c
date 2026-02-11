ctpl_value_to_string (const CtplValue *value)
{
  gchar *val = NULL;

  switch (ctpl_value_get_held_type (value)) {
    case CTPL_VTYPE_ARRAY: {

      const GSList *subvalues;
      GString      *string;

      string = g_string_new ("[");
      for (subvalues = ctpl_value_get_array (value);
           subvalues;
           subvalues = subvalues->next) {
        gchar *item;

        item = ctpl_value_to_string (subvalues->data);
        g_string_append (string, item);
        g_free (item);

        if (subvalues->next) {
          g_string_append (string, ", ");
        }
      }
      g_string_append (string, "]");
      val = g_string_free (string, FALSE);
      break;
    }

    case CTPL_VTYPE_FLOAT:
      val = ctpl_math_float_to_string (value->value.v_float);
      break;

    case CTPL_VTYPE_INT:
      val = g_strdup_printf ("%ld", value->value.v_int);
      break;

    case CTPL_VTYPE_STRING:
      val = g_strdup (value->value.v_string);
      break;
  }

  return val;
}
