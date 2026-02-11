folks_small_set_clear (GeeAbstractCollection *collection)
{
  FolksSmallSet *self = FOLKS_SMALL_SET (collection);

  g_return_if_fail (self != NULL);
  g_return_if_fail ((self->flags & FOLKS_SMALL_SET_FLAG_READ_ONLY) == 0);

  g_ptr_array_set_size (self->items, 0);
}
