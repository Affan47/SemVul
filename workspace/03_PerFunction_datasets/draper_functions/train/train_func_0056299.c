gst_object_set_parent (GstObject * object, GstObject * parent)
{
  g_return_val_if_fail (GST_IS_OBJECT (object), FALSE);
  g_return_val_if_fail (GST_IS_OBJECT (parent), FALSE);
  g_return_val_if_fail (object != parent, FALSE);

  GST_CAT_DEBUG_OBJECT (GST_CAT_REFCOUNTING, object,
      "set parent (ref and sink)");

  GST_OBJECT_LOCK (object);
  if (G_UNLIKELY (object->parent != NULL))
    goto had_parent;


  object->parent = parent;
  if (G_LIKELY (GST_OBJECT_IS_FLOATING (object))) {
    GST_CAT_TRACE_OBJECT (GST_CAT_REFCOUNTING, object,
        "unsetting floating flag");
    GST_OBJECT_FLAG_UNSET (object, GST_OBJECT_FLOATING);
    GST_OBJECT_UNLOCK (object);
  } else {
    GST_OBJECT_UNLOCK (object);
    gst_object_ref (object);
  }

  g_signal_emit (object, gst_object_signals[PARENT_SET], 0, parent);

  return TRUE;


had_parent:
  {
    GST_CAT_DEBUG_OBJECT (GST_CAT_REFCOUNTING, object,
        "set parent failed, object already had a parent");
    GST_OBJECT_UNLOCK (object);
    return FALSE;
  }
}
