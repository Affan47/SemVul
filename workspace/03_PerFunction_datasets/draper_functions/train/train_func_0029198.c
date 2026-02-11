folks_small_set_iterator_remove (GeeIterator *iter)
{
  FolksSmallSetIterator *self = FOLKS_SMALL_SET_ITERATOR (iter);

  g_return_if_fail (self != NULL);
  g_return_if_fail ((self->set->flags & FOLKS_SMALL_SET_FLAG_READ_ONLY) == 0);
  g_return_if_fail (_iterator_flag (self, ITER_STARTED));
  g_return_if_fail (!_iterator_flag (self, ITER_REMOVED));


  g_ptr_array_remove_index_fast (self->set->items, self->i);


  self->i--;


  self->flags |= ITER_REMOVED;
}
