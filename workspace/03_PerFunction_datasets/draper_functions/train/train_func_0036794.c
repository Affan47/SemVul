pendingproc_add_favourite_contact (TplActionChain *action_chain,
    gpointer user_data)
{
  FavouriteContactClosure *closure = user_data;
  gboolean should_add = FALSE;
  GError *error = NULL;

  g_return_if_fail (closure);
  g_return_if_fail (TPL_IS_DBUS_SERVICE (closure->service));
  g_return_if_fail (closure->context != NULL);

  if (!tp_dbus_check_valid_object_path (closure->account, &error))
    {
      dbus_g_method_return_error (closure->context, error);

      goto pendingproc_add_favourite_contact_ERROR;
    }

  should_add = favourite_contacts_add_event (closure->service, closure->account,
      closure->contact_id);

  closure->cb = add_favourite_contact_file_save_cb;

  if (should_add)
    favourite_contacts_file_save_async (closure->service, closure);
  else
    add_favourite_contact_file_save_cb (FALSE, closure);

  return;

pendingproc_add_favourite_contact_ERROR:
  if (action_chain != NULL)
    _tpl_action_chain_terminate (action_chain, error);

  g_clear_error (&error);
}
