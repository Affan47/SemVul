tp_tests_simple_account_manager_create_account (TpSvcAccountManager *svc,
    const gchar *in_Connection_Manager,
    const gchar *in_Protocol,
    const gchar *in_Display_Name,
    GHashTable *in_Parameters,
    GHashTable *in_Properties,
    DBusGMethodInvocation *context)
{
  TpTestsSimpleAccountManager *self = (TpTestsSimpleAccountManager *) svc;
  const gchar *out = TP_ACCOUNT_OBJECT_PATH_BASE "gabble/jabber/lospolloshermanos";


  if (!tp_strdiff (tp_asv_get_string (in_Parameters, "fail"), "yes"))
    {
      GError e = { TP_ERROR, TP_ERROR_INVALID_ARGUMENT, "loldongs" };
      dbus_g_method_return_error (context, &e);
      return;
    }

  self->create_cm = g_strdup (in_Connection_Manager);
  self->create_protocol = g_strdup (in_Protocol);
  self->create_display_name = g_strdup (in_Display_Name);
  self->create_parameters = g_hash_table_ref (in_Parameters);
  self->create_properties = g_hash_table_ref (in_Properties);

  tp_svc_account_manager_return_from_create_account (context, out);
}
