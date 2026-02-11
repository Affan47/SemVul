_tp_account_manager_name_owner_cb (TpDBusDaemon *proxy,
    const gchar *name,
    const gchar *new_owner,
    gpointer user_data)
{
  DEBUG ("Name owner changed for %s, new name: %s", name, new_owner);

  if (tp_str_empty (new_owner))
    {

      _tp_account_manager_start_mc5 (proxy);
      return;
    }
}
