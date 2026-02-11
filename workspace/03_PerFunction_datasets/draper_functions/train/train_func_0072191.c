gst_ximagesink_reset (GstXImageSink * ximagesink)
{
  GThread *thread;

  GST_OBJECT_LOCK (ximagesink);
  ximagesink->running = FALSE;

  thread = ximagesink->event_thread;
  ximagesink->event_thread = NULL;
  GST_OBJECT_UNLOCK (ximagesink);


  if (thread)
    g_thread_join (thread);

  if (ximagesink->ximage) {
    gst_buffer_unref (GST_BUFFER_CAST (ximagesink->ximage));
    ximagesink->ximage = NULL;
  }
  if (ximagesink->cur_image) {
    gst_buffer_unref (GST_BUFFER_CAST (ximagesink->cur_image));
    ximagesink->cur_image = NULL;
  }

  gst_ximagesink_bufferpool_clear (ximagesink);

  g_mutex_lock (ximagesink->flow_lock);
  if (ximagesink->xwindow) {
    gst_ximagesink_xwindow_clear (ximagesink, ximagesink->xwindow);
    gst_ximagesink_xwindow_destroy (ximagesink, ximagesink->xwindow);
    ximagesink->xwindow = NULL;
  }
  g_mutex_unlock (ximagesink->flow_lock);

  gst_ximagesink_xcontext_clear (ximagesink);
}
