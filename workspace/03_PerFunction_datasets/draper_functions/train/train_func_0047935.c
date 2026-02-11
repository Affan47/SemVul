get_current_position (GnlComposition * comp)
{
  GstFormat format = GST_FORMAT_TIME;
  gint64 value = GST_CLOCK_TIME_NONE;
  GstPad *pad;
  GnlObject *obj;
  gboolean res;


  if (comp->priv->ghostpad) {
    GstPad *peer = gst_pad_get_peer (comp->priv->ghostpad);
    if (peer) {
      res = gst_pad_query_position (peer, &format, &value);
      gst_object_unref (peer);
      if (res && (format == GST_FORMAT_TIME)) {
        GST_LOG_OBJECT (comp,
            "Successfully got downstream position %" GST_TIME_FORMAT,
            GST_TIME_ARGS ((guint64) value));
        goto beach;
      }
    }
    GST_DEBUG_OBJECT (comp, "Downstream position query failed");

    format = GST_FORMAT_TIME;
    value = GST_CLOCK_TIME_NONE;
  }


  if (!comp->priv->current) {
    GST_DEBUG_OBJECT (comp, "No current stack, can't send query");
    goto beach;
  }

  obj = (GnlObject *) comp->priv->current->data;

  if (!(pad = get_src_pad ((GstElement *) obj)))
    goto beach;

  res = gst_pad_query_position (pad, &format, &value);

  if (G_UNLIKELY ((res == FALSE) || (format != GST_FORMAT_TIME))) {
    GST_WARNING_OBJECT (comp,
        "query failed or returned a format different from TIME");
    value = GST_CLOCK_TIME_NONE;
  } else {
    GST_LOG_OBJECT (comp, "Query returned %" GST_TIME_FORMAT,
        GST_TIME_ARGS ((guint64) value));
  }

beach:
  return (guint64) value;
}
