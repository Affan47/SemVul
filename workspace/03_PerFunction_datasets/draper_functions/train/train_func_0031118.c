gst_collect_pads_default_collected (GstCollectPads * pads, gpointer user_data)
{
  GstCollectData *best = NULL;
  GstBuffer *buffer;
  GstFlowReturn ret = GST_FLOW_OK;
  GstCollectPadsBufferFunction func;
  gpointer buffer_user_data;

  g_return_val_if_fail (GST_IS_COLLECT_PADS (pads), GST_FLOW_ERROR);

  GST_OBJECT_LOCK (pads);
  func = pads->priv->buffer_func;
  buffer_user_data = pads->priv->buffer_user_data;
  GST_OBJECT_UNLOCK (pads);

  g_return_val_if_fail (func != NULL, GST_FLOW_NOT_SUPPORTED);


  if (gst_collect_pads_recalculate_full (pads)) {


    ret = GST_FLOW_OK;
    goto done;
  }

  best = pads->priv->earliest_data;


  if (G_UNLIKELY (best == NULL)) {
    ret = func (pads, best, NULL, buffer_user_data);
    if (ret == GST_FLOW_OK)
      ret = GST_FLOW_EOS;
    goto done;
  }


  gst_collect_pads_set_waiting (pads, best, TRUE);


  buffer = gst_collect_pads_pop (pads, best);
  ret = func (pads, best, buffer, buffer_user_data);


  gst_collect_pads_recalculate_full (pads);

done:
  return ret;
}
