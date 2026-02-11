example_contact_list_store_contacts_async (
    TpBaseContactList *contact_list,
    TpHandleSet *contacts,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  ExampleContactList *self = EXAMPLE_CONTACT_LIST (contact_list);
  TpHandleSet *changed = tp_handle_set_new (self->priv->contact_repo);
  TpIntsetFastIter iter;
  TpHandle member;

  tp_intset_fast_iter_init (&iter, tp_handle_set_peek (contacts));

  while (tp_intset_fast_iter_next (&iter, &member))
    {


      if (lookup_contact (self, member) == NULL)
        {
          gboolean created;

          ensure_contact (self, member, &created);
          send_updated_roster (self, member);


          if (created)
            tp_handle_set_add (changed, member);
        }
    }

  tp_base_contact_list_contacts_changed (contact_list, changed, NULL);

  tp_simple_async_report_success_in_idle ((GObject *) self, callback,
      user_data, example_contact_list_store_contacts_async);
}
