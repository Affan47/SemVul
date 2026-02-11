set_hat_cb (TpConnection *conn,
    const GError *error,
    gpointer user_data,
    GObject *weak_object)
{
  ContactPair *pair = user_data;
  GArray *handles = NULL;
  TpHandle handle;

  if (die_if (error, "SetHat()"))
    return;

  handles = g_array_sized_new (FALSE, FALSE, sizeof (TpHandle), 2);
  handle = tp_contact_get_handle (pair->contacts[0]);
  g_array_append_val (handles, handle);
  handle = tp_contact_get_handle (pair->contacts[1]);
  g_array_append_val (handles, handle);

  example_cli_connection_interface_hats_call_get_hats (conn, -1,
      handles, got_hats_cb, NULL, NULL, NULL);
}
