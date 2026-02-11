tp_tests_connection_run_until_contact_by_id (TpConnection *connection,
    const gchar *id,
    guint n_features,
    const TpContactFeature *features)
{
  TpContact *contact = NULL;

  tp_connection_dup_contact_by_id_async (connection, id, n_features, features,
      one_contact_cb, &contact);

  while (contact == NULL)
    g_main_context_iteration (NULL, TRUE);

  return contact;
}
