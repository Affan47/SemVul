gst_ximagesink_change_state (GstElement * element, GstStateChange transition)
{
  GstXImageSink *ximagesink;
  GstStateChangeReturn ret = GST_STATE_CHANGE_SUCCESS;
  GstXContext *xcontext = NULL;

  ximagesink = GST_XIMAGESINK (element);

  switch (transition) {
    case GST_STATE_CHANGE_NULL_TO_READY:


      if (ximagesink->xcontext == NULL) {
        xcontext = gst_ximagesink_xcontext_get (ximagesink);
        if (xcontext == NULL) {
          ret = GST_STATE_CHANGE_FAILURE;
          goto beach;
        }
        GST_OBJECT_LOCK (ximagesink);
        if (xcontext)
          ximagesink->xcontext = xcontext;
        GST_OBJECT_UNLOCK (ximagesink);
      }


      GST_DEBUG_OBJECT (ximagesink, "XSynchronize called with %s",
          ximagesink->synchronous ? "TRUE" : "FALSE");
      g_mutex_lock (ximagesink->x_lock);
      XSynchronize (ximagesink->xcontext->disp, ximagesink->synchronous);
      g_mutex_unlock (ximagesink->x_lock);
      gst_ximagesink_manage_event_thread (ximagesink);
      break;
    case GST_STATE_CHANGE_READY_TO_PAUSED:
      g_mutex_lock (ximagesink->flow_lock);
      if (ximagesink->xwindow)
        gst_ximagesink_xwindow_clear (ximagesink, ximagesink->xwindow);
      g_mutex_unlock (ximagesink->flow_lock);
      break;
    case GST_STATE_CHANGE_PAUSED_TO_PLAYING:
      break;
    default:
      break;
  }

  ret = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    case GST_STATE_CHANGE_PLAYING_TO_PAUSED:
      break;
    case GST_STATE_CHANGE_PAUSED_TO_READY:
      ximagesink->fps_n = 0;
      ximagesink->fps_d = 1;
      GST_VIDEO_SINK_WIDTH (ximagesink) = 0;
      GST_VIDEO_SINK_HEIGHT (ximagesink) = 0;
      break;
    case GST_STATE_CHANGE_READY_TO_NULL:
      gst_ximagesink_reset (ximagesink);
      break;
    default:
      break;
  }

beach:
  return ret;
}
