gst_parse_element_set (gchar *value, GstElement *element, graph_t *graph)
{
  GParamSpec *pspec;
  gchar *pos = value;
  GValue v = { 0, };
  GstObject *target = NULL;
  GType value_type;


  if (element == NULL)
    goto out;


  while (!g_ascii_isspace (*pos) && (*pos != '=')) pos++;
  if (*pos == '=') {
    *pos = '\0';
  } else {
    *pos = '\0';
    pos++;
    while (g_ascii_isspace (*pos)) pos++;
  }
  pos++;
  while (g_ascii_isspace (*pos)) pos++;
  if (*pos == '"') {
    pos++;
    pos[strlen (pos) - 1] = '\0';
  }
  gst_parse_unescape (pos);

  if (gst_child_proxy_lookup (GST_OBJECT (element), value, &target, &pspec)) {
    gboolean got_value = FALSE;

    value_type = pspec->value_type;

    GST_CAT_LOG_OBJECT (GST_CAT_PIPELINE, element, "parsing property %s as a %s", pspec->name,
      g_type_name (value_type));
    g_value_init (&v, value_type);
    if (gst_value_deserialize (&v, pos))
      got_value = TRUE;
    else if (g_type_is_a (value_type, GST_TYPE_ELEMENT)) {
       GstElement *bin;

       bin = gst_parse_bin_from_description (pos, TRUE, NULL);
       if (bin) {
         g_value_set_object (&v, bin);
         got_value = TRUE;
       }
    }
    if (!got_value)
      goto error;
    g_object_set_property (G_OBJECT (target), pspec->name, &v);
  } else {

    if (GST_IS_CHILD_PROXY (element)) {
      gst_parse_add_delayed_set (element, value, pos);
    }
    else {
      SET_ERROR (graph->error, GST_PARSE_ERROR_NO_SUCH_PROPERTY, \
          _("no property \"%s\" in element \"%s\""), value, \
          GST_ELEMENT_NAME (element));
    }
  }

out:
  gst_parse_strfree (value);
  if (G_IS_VALUE (&v))
    g_value_unset (&v);
  if (target)
    gst_object_unref (target);
  return;

error:
  SET_ERROR (graph->error, GST_PARSE_ERROR_COULD_NOT_SET_PROPERTY,
         _("could not set property \"%s\" in element \"%s\" to \"%s\""),
	 value, GST_ELEMENT_NAME (element), pos);
  goto out;
}
