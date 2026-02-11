gst_iterator_next (GstIterator * it, gpointer * elem)
{
  GstIteratorResult result;

  g_return_val_if_fail (it != NULL, GST_ITERATOR_ERROR);
  g_return_val_if_fail (elem != NULL, GST_ITERATOR_ERROR);

restart:
  if (it->pushed) {
    result = gst_iterator_next (it->pushed, elem);
    if (result == GST_ITERATOR_DONE) {


      gst_iterator_pop (it);
    } else {
      return result;
    }
  }

  if (G_LIKELY (it->lock))
    g_mutex_lock (it->lock);

  if (G_UNLIKELY (*it->master_cookie != it->cookie)) {
    result = GST_ITERATOR_RESYNC;
    goto done;
  }

  result = it->next (it, elem);
  if (result == GST_ITERATOR_OK && it->item) {
    GstIteratorItem itemres;

    itemres = it->item (it, *elem);
    switch (itemres) {
      case GST_ITERATOR_ITEM_SKIP:
        if (G_LIKELY (it->lock))
          g_mutex_unlock (it->lock);
        goto restart;
      case GST_ITERATOR_ITEM_END:
        result = GST_ITERATOR_DONE;
        break;
      case GST_ITERATOR_ITEM_PASS:
        break;
    }
  }

done:
  if (G_LIKELY (it->lock))
    g_mutex_unlock (it->lock);

  return result;
}
