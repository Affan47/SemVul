gst_queue2_src_activate_push (GstPad * pad, gboolean active)
{
  gboolean result = FALSE;
  GstQueue2 *queue;

  queue = GST_QUEUE2 (gst_pad_get_parent (pad));

  if (active) {
    GST_QUEUE2_MUTEX_LOCK (queue);
    GST_DEBUG_OBJECT (queue, "activating push mode");
    queue->srcresult = GST_FLOW_OK;
    queue->sinkresult = GST_FLOW_OK;
    queue->is_eos = FALSE;
    queue->unexpected = FALSE;
    result = gst_pad_start_task (pad, (GstTaskFunction) gst_queue2_loop, pad);
    GST_QUEUE2_MUTEX_UNLOCK (queue);
  } else {

    GST_QUEUE2_MUTEX_LOCK (queue);
    GST_DEBUG_OBJECT (queue, "deactivating push mode");
    queue->srcresult = GST_FLOW_WRONG_STATE;
    queue->sinkresult = GST_FLOW_WRONG_STATE;

    GST_QUEUE2_SIGNAL_ADD (queue);
    GST_QUEUE2_MUTEX_UNLOCK (queue);


    result = gst_pad_stop_task (pad);
  }

  gst_object_unref (queue);

  return result;
}
