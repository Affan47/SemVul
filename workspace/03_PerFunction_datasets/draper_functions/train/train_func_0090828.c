gst_base_sink_queue_object_unlocked (GstBaseSink * basesink, GstPad * pad,
    guint8 obj_type, gpointer obj, gboolean prerollable)
{
  GstFlowReturn ret = GST_FLOW_OK;
  gint length;
  GQueue *q;

  if (G_UNLIKELY (basesink->need_preroll)) {
    if (G_LIKELY (prerollable))
      basesink->preroll_queued++;

    length = basesink->preroll_queued;

    GST_DEBUG_OBJECT (basesink, "now %d prerolled items", length);


    if (length == 1) {
      ret = gst_base_sink_preroll_object (basesink, obj_type, obj);
      if (G_UNLIKELY (ret != GST_FLOW_OK))
        goto preroll_failed;
    }


    if (G_UNLIKELY (basesink->need_preroll)) {


      if (G_UNLIKELY (length <= basesink->preroll_queue_max_len))
        goto more_preroll;
    }
  }


  q = basesink->preroll_queue;
  while (G_UNLIKELY (!g_queue_is_empty (q))) {
    GstMiniObject *o;
    guint8 ot;

    o = g_queue_pop_head (q);
    GST_DEBUG_OBJECT (basesink, "rendering queued object %p", o);

    ot = get_object_type (o);


    ret = gst_base_sink_render_object (basesink, pad, ot, o);
    if (ret != GST_FLOW_OK)
      goto dequeue_failed;
  }


  ret = gst_base_sink_render_object (basesink, pad, obj_type, obj);
  basesink->preroll_queued = 0;

  return ret;


preroll_failed:
  {
    GST_DEBUG_OBJECT (basesink, "preroll failed, reason %s",
        gst_flow_get_name (ret));
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (obj));
    return ret;
  }
more_preroll:
  {

    GST_DEBUG_OBJECT (basesink, "need more preroll data %d <= %d",
        length, basesink->preroll_queue_max_len);
    g_queue_push_tail (basesink->preroll_queue, obj);
    return GST_FLOW_OK;
  }
dequeue_failed:
  {
    GST_DEBUG_OBJECT (basesink, "rendering queued objects failed, reason %s",
        gst_flow_get_name (ret));
    gst_mini_object_unref (GST_MINI_OBJECT_CAST (obj));
    return ret;
  }
}
