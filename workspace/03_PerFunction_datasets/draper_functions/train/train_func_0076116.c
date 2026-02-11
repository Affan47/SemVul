contacts_queue_item_set_contacts (ContactsQueueItem *item,
    guint n_contacts,
    TpContact * const *contacts)
{
  guint i;

  g_assert (item->contacts == NULL);
  item->contacts = g_ptr_array_new_full (n_contacts, g_object_unref);
  for (i = 0; i < n_contacts; i++)
    g_ptr_array_add (item->contacts, g_object_ref (contacts[i]));
}
