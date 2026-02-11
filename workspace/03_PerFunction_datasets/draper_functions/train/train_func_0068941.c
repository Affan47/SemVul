gst_progress_report_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstProgressReport *filter;

  filter = GST_PROGRESS_REPORT (object);

  switch (prop_id) {
    case ARG_UPDATE_FREQ:
      GST_OBJECT_LOCK (filter);
      filter->update_freq = g_value_get_int (value);
      GST_OBJECT_UNLOCK (filter);
      break;
    case ARG_SILENT:
      GST_OBJECT_LOCK (filter);
      filter->silent = g_value_get_boolean (value);
      GST_OBJECT_UNLOCK (filter);
      break;
    case ARG_DO_QUERY:
      GST_OBJECT_LOCK (filter);
      filter->do_query = g_value_get_boolean (value);
      GST_OBJECT_UNLOCK (filter);
      break;
    case ARG_FORMAT:
      GST_OBJECT_LOCK (filter);
      g_free (filter->format);
      filter->format = g_value_dup_string (value);
      if (filter->format == NULL)
        filter->format = g_strdup ("auto");
      GST_OBJECT_UNLOCK (filter);
      break;
    default:
      break;
  }
}
