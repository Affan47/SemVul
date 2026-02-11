gst_base_src_event (GstPad * pad, GstObject * parent, GstEvent * event)
{
  GstBaseSrc *src;
  GstBaseSrcClass *bclass;
  gboolean result = FALSE;

  src = GST_BASE_SRC (parent);
  bclass = GST_BASE_SRC_GET_CLASS (src);

  if (bclass->event) {
    if (!(result = bclass->event (src, event)))
      goto subclass_failed;
  }

done:
  gst_event_unref (event);

  return result;


subclass_failed:
  {
    GST_DEBUG_OBJECT (src, "subclass refused event");
    goto done;
  }
}
