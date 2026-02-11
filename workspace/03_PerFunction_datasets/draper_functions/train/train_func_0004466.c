gst_mini_object_is_writable (const GstMiniObject * mini_object)
{
  g_return_val_if_fail (mini_object != NULL, FALSE);

  return (GST_MINI_OBJECT_REFCOUNT_VALUE (mini_object) == 1) &&
      ((mini_object->flags & GST_MINI_OBJECT_FLAG_READONLY) == 0);
}
