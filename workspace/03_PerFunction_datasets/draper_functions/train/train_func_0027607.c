gst_iterator_filter (GstIterator * it, GCompareFunc func,
    const GValue * user_data)
{
  GstIteratorFilter *result;

  g_return_val_if_fail (it != NULL, NULL);
  g_return_val_if_fail (func != NULL, NULL);

  result = (GstIteratorFilter *) gst_iterator_new (sizeof (GstIteratorFilter),
      it->type, it->lock, it->master_cookie,
      (GstIteratorCopyFunction) filter_copy,
      (GstIteratorNextFunction) filter_next,
      (GstIteratorItemFunction) NULL,
      (GstIteratorResyncFunction) filter_resync,
      (GstIteratorFreeFunction) filter_free);

  it->lock = NULL;
  result->func = func;
  if (user_data) {
    g_value_init (&result->user_data, G_VALUE_TYPE (user_data));
    g_value_copy (user_data, &result->user_data);
    result->have_user_data = TRUE;
  } else {
    result->have_user_data = FALSE;
  }
  result->slave = it;

  return GST_ITERATOR (result);
}
