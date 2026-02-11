eci_impl_los_list_alloc_item(void)
{
  struct eci_los_list *item;

  item = (struct eci_los_list*)calloc(1, sizeof(struct eci_los_list));
  DBC_CHECK(item != NULL);
  item->next_repp = item->prev_repp = NULL;
  eci_string_clear(&item->data_repp);

  return item;
}
