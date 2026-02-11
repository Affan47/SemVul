folks_small_set_finalize (GObject *obj)
{
  FolksSmallSet *self = FOLKS_SMALL_SET (obj);

  g_ptr_array_unref (self->items);

  if (self->item_hash_data_free != NULL)
    self->item_hash_data_free (self->item_hash_data);

  if (self->item_equals_data_free != NULL)
    self->item_equals_data_free (self->item_equals_data);

  ((GObjectClass *) folks_small_set_parent_class)->finalize (obj);
}
