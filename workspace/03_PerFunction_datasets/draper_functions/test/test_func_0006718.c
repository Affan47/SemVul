gst_ximagesink_manage_event_thread (GstXImageSink * ximagesink)
{
  GThread *thread = NULL;


  if (ximagesink->xcontext == NULL) {
    return;
  }

  GST_OBJECT_LOCK (ximagesink);
  if (ximagesink->handle_expose || ximagesink->handle_events) {
    if (!ximagesink->event_thread) {

      GST_DEBUG_OBJECT (ximagesink, "run xevent thread, expose %d, events %d",
          ximagesink->handle_expose, ximagesink->handle_events);
      ximagesink->running = TRUE;
      ximagesink->event_thread = g_thread_try_new ("ximagesink-events",
          (GThreadFunc) gst_ximagesink_event_thread, ximagesink, NULL);
    }
  } else {
    if (ximagesink->event_thread) {
      GST_DEBUG_OBJECT (ximagesink, "stop xevent thread, expose %d, events %d",
          ximagesink->handle_expose, ximagesink->handle_events);
      ximagesink->running = FALSE;

      thread = ximagesink->event_thread;
      ximagesink->event_thread = NULL;
    }
  }
  GST_OBJECT_UNLOCK (ximagesink);


  if (thread)
    g_thread_join (thread);

}
