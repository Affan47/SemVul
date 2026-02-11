internalpad_query_function (GstPad * internal, GstObject * parent,
    GstQuery * query)
{
  GnlPadPrivate *priv = gst_pad_get_element_private (internal);
  GnlObject *object = priv->object;
  gboolean ret;

  GST_DEBUG_OBJECT (internal, "querytype:%s",
      gst_query_type_get_name (GST_QUERY_TYPE (query)));

  if (!(priv->queryfunc)) {
    GST_WARNING_OBJECT (internal,
        "priv->queryfunc == NULL !! What is going on ?");
    return FALSE;
  }

  if ((ret = priv->queryfunc (internal, parent, query))) {

    switch (priv->dir) {
      case GST_PAD_SRC:
        break;
      case GST_PAD_SINK:
        switch (GST_QUERY_TYPE (query)) {
          case GST_QUERY_POSITION:
            ret = translate_outgoing_position_query (object, query);
            break;
          default:
            break;
        }
        break;
      default:
        break;
    }
  }
  return ret;
}
