get_object_type (GstMiniObject * obj)
{
  guint8 obj_type;

  if (G_LIKELY (GST_IS_BUFFER (obj)))
    obj_type = _PR_IS_BUFFER;
  else if (GST_IS_EVENT (obj))
    obj_type = _PR_IS_EVENT;
  else if (GST_IS_BUFFER_LIST (obj))
    obj_type = _PR_IS_BUFFERLIST;
  else
    obj_type = _PR_IS_NOTHING;

  return obj_type;
}
