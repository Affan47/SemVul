gst_type_find_helper_for_buffer (GstObject * obj, GstBuffer * buf,
    GstTypeFindProbability * prob)
{
  GstTypeFindBufHelper helper;
  GstTypeFind find;
  GList *l, *type_list;
  GstCaps *result = NULL;

  g_return_val_if_fail (buf != NULL, NULL);
  g_return_val_if_fail (GST_IS_BUFFER (buf), NULL);
  g_return_val_if_fail (GST_BUFFER_OFFSET (buf) == 0 ||
      GST_BUFFER_OFFSET (buf) == GST_BUFFER_OFFSET_NONE, NULL);

  helper.data = GST_BUFFER_DATA (buf);
  helper.size = GST_BUFFER_SIZE (buf);
  helper.best_probability = GST_TYPE_FIND_NONE;
  helper.caps = NULL;
  helper.obj = obj;

  if (helper.data == NULL || helper.size == 0)
    return NULL;

  find.data = &helper;
  find.peek = buf_helper_find_peek;
  find.suggest = buf_helper_find_suggest;
  find.get_length = NULL;

  type_list = gst_type_find_factory_get_list ();

  for (l = type_list; l; l = l->next) {
    helper.factory = GST_TYPE_FIND_FACTORY (l->data);
    gst_type_find_factory_call_function (helper.factory, &find);
    if (helper.best_probability >= GST_TYPE_FIND_MAXIMUM)
      break;
  }
  gst_plugin_feature_list_free (type_list);

  if (helper.best_probability > 0)
    result = helper.caps;

  if (prob)
    *prob = helper.best_probability;

  GST_LOG_OBJECT (obj, "Returning %" GST_PTR_FORMAT " (probability = %u)",
      result, (guint) helper.best_probability);

  return result;
}
