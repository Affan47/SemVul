gst_object_get_parent (GstObject * object)
{
  GstObject *result = NULL;

  g_return_val_if_fail (GST_IS_OBJECT (object), NULL);

  GST_OBJECT_LOCK (object);
  result = object->parent;
  if (G_LIKELY (result))
    gst_object_ref (result);
  GST_OBJECT_UNLOCK (object);

  return result;
}
