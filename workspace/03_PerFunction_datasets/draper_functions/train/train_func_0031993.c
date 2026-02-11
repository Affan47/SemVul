pendingproc_remove_favourite_contact (TplActionChain *action_chain,
    gpointer user_data)
{
  FavouriteContactClosure *closure = user_data;
  GHashTable *contacts;
  gboolean removed = FALSE;
  GError *error = NULL;

  g_return_if_fail (closure != NULL);
  g_return_if_fail (TPL_IS_DBUS_SERVICE (closure->service));
  g_return_if_fail (closure->context != NULL);

  TplDBusServicePriv *priv = closure->service->priv;

  if (!tp_dbus_check_valid_object_path (closure->account, &error))
    {
      dbus_g_method_return_error (closure->context, error);

      goto pendingproc_remove_favourite_contact_ERROR;
    }

  DEBUG ("removing favourite contact: account '%s', ID '%s'",
      closure->account, closure->contact_id);

  contacts = g_hash_table_lookup (priv->accounts_contacts_map,
      closure->account);
  if (contacts != NULL && g_hash_table_remove (contacts, closure->contact_id))
      removed = TRUE;

  closure->cb = remove_favourite_contact_file_save_cb;

  if (removed)
    favourite_contacts_file_save_async (closure->service, closure);
  else
    remove_favourite_contact_file_save_cb (FALSE, closure);

  return;

pendingproc_remove_favourite_contact_ERROR:
  if (action_chain != NULL)
    _tpl_action_chain_terminate (action_chain, error);

  g_clear_error (&error);
}
