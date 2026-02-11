gst_debug_print_segment (gpointer ptr)
{
  GstSegment *segment = (GstSegment *) ptr;


  if (segment == NULL) {
    return g_strdup ("(NULL)");
  }

  switch (segment->format) {
    case GST_FORMAT_UNDEFINED:{
      return g_strdup_printf ("UNDEFINED segment");
    }
    case GST_FORMAT_TIME:{
      return g_strdup_printf ("time segment start=%" GST_TIME_FORMAT
          ", stop=%" GST_TIME_FORMAT ", last_stop=%" GST_TIME_FORMAT
          ", duration=%" GST_TIME_FORMAT ", rate=%f, applied_rate=%f"
          ", flags=0x%02x, time=%" GST_TIME_FORMAT ", accum=%" GST_TIME_FORMAT,
          GST_TIME_ARGS (segment->start), GST_TIME_ARGS (segment->stop),
          GST_TIME_ARGS (segment->last_stop), GST_TIME_ARGS (segment->duration),
          segment->rate, segment->applied_rate, (guint) segment->flags,
          GST_TIME_ARGS (segment->time), GST_TIME_ARGS (segment->accum));
    }
    default:{
      const gchar *format_name;

      format_name = gst_format_get_name (segment->format);
      if (G_UNLIKELY (format_name == NULL))
        format_name = "(UNKNOWN FORMAT)";
      return g_strdup_printf ("%s segment start=%" G_GINT64_FORMAT
          ", stop=%" G_GINT64_FORMAT ", last_stop=%" G_GINT64_FORMAT
          ", duration=%" G_GINT64_FORMAT ", rate=%f, applied_rate=%f"
          ", flags=0x%02x, time=%" GST_TIME_FORMAT ", accum=%" GST_TIME_FORMAT,
          format_name, segment->start, segment->stop, segment->last_stop,
          segment->duration, segment->rate, segment->applied_rate,
          (guint) segment->flags, GST_TIME_ARGS (segment->time),
          GST_TIME_ARGS (segment->accum));
    }
  }
}
