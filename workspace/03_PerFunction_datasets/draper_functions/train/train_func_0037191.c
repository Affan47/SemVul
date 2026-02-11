contacts_requested_handles (TpConnection *connection,
                            TpHandleType handle_type,
                            guint n_handles,
                            const TpHandle *handles,
                            const gchar * const *ids,
                            const GError *error,
                            gpointer user_data,
                            GObject *weak_object)
{
  ContactsContext *c = user_data;

  g_assert (handle_type == TP_HANDLE_TYPE_CONTACT);
  g_assert (weak_object == c->weak_object);

  if (error == NULL)
    {
      guint i;

      for (i = 0; i < n_handles; i++)
        {
          TpContact *contact = tp_contact_ensure (connection, handles[i]);

          g_array_append_val (c->handles, handles[i]);
          g_ptr_array_add (c->contacts, contact);
        }
    }
  else if (error->domain == TP_ERROR &&
      (error->code == TP_ERROR_INVALID_HANDLE ||
       error->code == TP_ERROR_NOT_AVAILABLE ||
       error->code == TP_ERROR_INVALID_ARGUMENT))
    {

      guint i;

      DEBUG ("A handle was bad, trying to recover: %s %u: %s",
          g_quark_to_string (error->domain), error->code, error->message);


      for (i = 0; i < c->request_ids->len - 1; i++)
        {
          g_queue_push_head (&c->todo, contacts_request_one_handle);
        }

      g_assert (c->next_index == 0);
    }
  else
    {
      DEBUG ("RequestHandles failed: %s %u: %s",
          g_quark_to_string (error->domain), error->code, error->message);
      contacts_context_fail (c, error);
      return;
    }

  contacts_context_continue (c);
}
