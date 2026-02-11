internalpad_event_function (GstPad * internal, GstObject * parent,
    GstEvent * event)
{
  GnlPadPrivate *priv = gst_pad_get_element_private (internal);
  GnlObject *object = priv->object;
  gboolean res;

  GST_DEBUG_OBJECT (internal, "event:%s (seqnum::%d)",
      GST_EVENT_TYPE_NAME (event), GST_EVENT_SEQNUM (event));

  if (G_UNLIKELY (!(priv->eventfunc))) {
    GST_WARNING_OBJECT (internal,
        "priv->eventfunc == NULL !! What is going on ?");
    return FALSE;
  }

  switch (priv->dir) {
    case GST_PAD_SRC:{
      switch (GST_EVENT_TYPE (event)) {
        case GST_EVENT_SEGMENT:
          event = translate_outgoing_segment (object, event);
          break;
        default:
          break;
      }

      break;
    }
    case GST_PAD_SINK:{
      switch (GST_EVENT_TYPE (event)) {
        case GST_EVENT_SEEK:
          event = translate_outgoing_seek (object, event);
          break;
        default:
          break;
      }
      break;
    }
    default:
      break;
  }
  GST_DEBUG_OBJECT (internal, "Calling priv->eventfunc %p", priv->eventfunc);
  res = priv->eventfunc (internal, parent, event);

  return res;
}
