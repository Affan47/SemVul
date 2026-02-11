gst_multi_queue_change_state (GstElement * element, GstStateChange transition)
{
  GstMultiQueue *mqueue = GST_MULTI_QUEUE (element);
  GstSingleQueue *sq = NULL;
  GstStateChangeReturn result;

  switch (transition) {
    case GST_STATE_CHANGE_READY_TO_PAUSED:{
      GList *tmp;


      GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);
      for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
        sq = (GstSingleQueue *) tmp->data;
        sq->flushing = FALSE;
      }
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);
      break;
    }
    case GST_STATE_CHANGE_PAUSED_TO_READY:{
      GList *tmp;


      GST_MULTI_QUEUE_MUTEX_LOCK (mqueue);
      for (tmp = mqueue->queues; tmp; tmp = g_list_next (tmp)) {
        sq = (GstSingleQueue *) tmp->data;
        sq->flushing = TRUE;
        g_cond_signal (sq->turn);
      }
      GST_MULTI_QUEUE_MUTEX_UNLOCK (mqueue);
      break;
    }
    default:
      break;
  }

  result = GST_ELEMENT_CLASS (parent_class)->change_state (element, transition);

  switch (transition) {
    default:
      break;
  }

  return result;


}
