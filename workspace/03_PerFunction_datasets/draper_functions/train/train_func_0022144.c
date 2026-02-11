example_contact_list_set_group_members_async (TpBaseContactList *contact_list,
    const gchar *group,
    TpHandleSet *contacts,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  ExampleContactList *self = EXAMPLE_CONTACT_LIST (contact_list);
  TpHandleSet *new_contacts = tp_handle_set_new (self->priv->contact_repo);
  TpHandleSet *added = tp_handle_set_new (self->priv->contact_repo);
  TpHandleSet *removed = tp_handle_set_new (self->priv->contact_repo);
  TpIntsetFastIter iter;
  TpHandle member;
  gchar *tag = ensure_tag (self, group, TRUE);

  tp_intset_fast_iter_init (&iter, tp_handle_set_peek (contacts));

  while (tp_intset_fast_iter_next (&iter, &member))
    {
      gboolean created = FALSE, updated = FALSE;
      ExampleContactDetails *d = ensure_contact (self, member, &created);

      if (created)
        tp_handle_set_add (new_contacts, member);

      if (d->tags == NULL)
        d->tags = g_hash_table_new (g_str_hash, g_str_equal);

      if (g_hash_table_lookup (d->tags, tag) == NULL)
        {
          g_hash_table_insert (d->tags, tag, tag);
          updated = TRUE;
        }

      if (created || updated)
        {
          send_updated_roster (self, member);
          tp_handle_set_add (added, member);
        }
    }

  tp_intset_fast_iter_init (&iter, tp_handle_set_peek (self->priv->contacts));

  while (tp_intset_fast_iter_next (&iter, &member))
    {
      ExampleContactDetails *d;

      if (tp_handle_set_is_member (contacts, member))
        continue;

      d = lookup_contact (self, member);

      if (d != NULL && d->tags != NULL && g_hash_table_remove (d->tags, group))
        tp_handle_set_add (removed, member);
    }

  if (!tp_handle_set_is_empty (new_contacts))
    tp_base_contact_list_contacts_changed (contact_list, new_contacts, NULL);

  if (!tp_handle_set_is_empty (added))
    tp_base_contact_list_groups_changed (contact_list, added, &group, 1,
        NULL, 0);

  if (!tp_handle_set_is_empty (removed))
    tp_base_contact_list_groups_changed (contact_list, removed, NULL, 0,
        &group, 1);

  tp_handle_set_destroy (added);
  tp_handle_set_destroy (removed);
  tp_handle_set_destroy (new_contacts);
  tp_simple_async_report_success_in_idle ((GObject *) self, callback,
      user_data, example_contact_list_set_group_members_async);
}
