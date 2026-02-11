gst_gdk_pixbuf_sink_event (GstPad * pad, GstEvent * event)
{
  GstFlowReturn res = GST_FLOW_OK;
  gboolean ret = TRUE;
  GstGdkPixbuf *pixbuf;

  pixbuf = GST_GDK_PIXBUF (gst_pad_get_parent (pad));

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_EOS:
      if (pixbuf->pixbuf_loader != NULL) {
        gdk_pixbuf_loader_close (pixbuf->pixbuf_loader, NULL);
        res = gst_gdk_pixbuf_flush (pixbuf);
        g_object_unref (G_OBJECT (pixbuf->pixbuf_loader));
        pixbuf->pixbuf_loader = NULL;


        if (res != GST_FLOW_OK && res != GST_FLOW_WRONG_STATE) {
          GST_ELEMENT_ERROR (pixbuf, STREAM, FAILED, (NULL),
              ("Flow: %s", gst_flow_get_name (res)));
        }
      }
      break;
    case GST_EVENT_NEWSEGMENT:
    case GST_EVENT_FLUSH_STOP:
      if (pixbuf->pixbuf_loader != NULL) {
        gdk_pixbuf_loader_close (pixbuf->pixbuf_loader, NULL);
        g_object_unref (G_OBJECT (pixbuf->pixbuf_loader));
        pixbuf->pixbuf_loader = NULL;
      }
      break;
    default:
      break;
  }

  if (res == GST_FLOW_OK) {
    ret = gst_pad_event_default (pad, event);
  } else {
    ret = FALSE;
  }

  gst_object_unref (pixbuf);

  return ret;
}
