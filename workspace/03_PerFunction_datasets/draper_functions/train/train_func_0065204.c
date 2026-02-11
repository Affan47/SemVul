one_contact_cb (GObject *object,
    GAsyncResult *result,
    gpointer user_data)
{
  TpConnection *connection = (TpConnection *) object;
  TpContact **contact_loc = user_data;
  GError *error = NULL;

  *contact_loc = tp_connection_dup_contact_by_id_finish (connection, result,
      &error);

  g_assert_no_error (error);
  g_assert (TP_IS_CONTACT (*contact_loc));
}
