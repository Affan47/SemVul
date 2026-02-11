_handle_ready_pending_cb (gpointer data)
{
  SwContactView *contact_view = SW_CONTACT_VIEW (data);
  SwContactViewPrivate *priv = GET_PRIVATE (contact_view);
  GList *contacts_to_send = NULL;
  GList *pending_contacts, *l;

  SW_DEBUG (VIEWS, "Delayed ready timeout fired");


  pending_contacts = sw_set_as_list (priv->pending_contacts_set);

  for (l = pending_contacts; l; l = l->next)
  {
    SwContact *contact = SW_CONTACT (l->data);

    if (sw_contact_get_ready (contact))
    {
      contacts_to_send = g_list_prepend (contacts_to_send, contact);
      sw_set_remove (priv->pending_contacts_set, (GObject *)contact);
    }
  }

  sw_contact_view_add_contacts (contact_view, contacts_to_send);

  g_list_free (pending_contacts);

  priv->pending_timeout_id = 0;

  return FALSE;
}
