gst_pad_start_task (GstPad * pad, GstTaskFunction func, gpointer data)
{
  GstTask *task;
  gboolean res;

  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);
  g_return_val_if_fail (func != NULL, FALSE);

  GST_DEBUG_OBJECT (pad, "start task");

  GST_OBJECT_LOCK (pad);
  task = GST_PAD_TASK (pad);
  if (task == NULL) {
    task = gst_task_create (func, data);
    gst_task_set_lock (task, GST_PAD_GET_STREAM_LOCK (pad));
    gst_task_set_thread_callbacks (task, &thr_callbacks, pad, NULL);
    GST_DEBUG_OBJECT (pad, "created task");
    GST_PAD_TASK (pad) = task;
    gst_object_ref (task);

    GST_OBJECT_UNLOCK (pad);

    do_stream_status (pad, GST_STREAM_STATUS_TYPE_CREATE, NULL, task);

    gst_object_unref (task);

    GST_OBJECT_LOCK (pad);

    if (GST_PAD_TASK (pad) != task)
      goto concurrent_stop;
  }
  res = gst_task_set_state (task, GST_TASK_STARTED);
  GST_OBJECT_UNLOCK (pad);

  return res;


concurrent_stop:
  {
    GST_OBJECT_UNLOCK (pad);
    return TRUE;
  }
}
