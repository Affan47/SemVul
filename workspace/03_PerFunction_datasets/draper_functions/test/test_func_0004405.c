gst_collect_pads_remove_pad (GstCollectPads * pads, GstPad * pad)
{
  GstCollectData *data;
  GSList *list;

  g_return_val_if_fail (pads != NULL, FALSE);
  g_return_val_if_fail (GST_IS_COLLECT_PADS (pads), FALSE);
  g_return_val_if_fail (pad != NULL, FALSE);
  g_return_val_if_fail (GST_IS_PAD (pad), FALSE);

  GST_DEBUG_OBJECT (pads, "removing pad %s:%s", GST_DEBUG_PAD_NAME (pad));

  GST_OBJECT_LOCK (pads);
  list =
      g_slist_find_custom (pads->priv->pad_list, pad, (GCompareFunc) find_pad);
  if (!list)
    goto unknown_pad;

  data = (GstCollectData *) list->data;

  GST_DEBUG_OBJECT (pads, "found pad %s:%s at %p", GST_DEBUG_PAD_NAME (pad),
      data);


  gst_pad_set_chain_function (pad, NULL);
  gst_pad_set_event_function (pad, NULL);
  GST_OBJECT_LOCK (pad);
  gst_pad_set_element_private (pad, NULL);
  GST_OBJECT_UNLOCK (pad);


  if (!pads->priv->started) {
    GSList *dlist;

    dlist = g_slist_find_custom (pads->data, pad, (GCompareFunc) find_pad);
    if (dlist) {
      GstCollectData *pdata = dlist->data;

      pads->data = g_slist_delete_link (pads->data, dlist);
      unref_data (pdata);
    }
  }

  pads->priv->pad_list = g_slist_delete_link (pads->priv->pad_list, list);
  pads->priv->pad_cookie++;


  GST_COLLECT_PADS_EVT_BROADCAST (pads);


  if (!pads->priv->started)
    gst_pad_set_active (pad, FALSE);


  unref_data (data);

  GST_OBJECT_UNLOCK (pads);

  return TRUE;

unknown_pad:
  {
    GST_WARNING_OBJECT (pads, "cannot remove unknown pad %s:%s",
        GST_DEBUG_PAD_NAME (pad));
    GST_OBJECT_UNLOCK (pads);
    return FALSE;
  }
}
