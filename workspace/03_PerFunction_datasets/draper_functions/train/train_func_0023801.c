_gnutls_selected_certs_deinit (gnutls_session_t session)
{
  if (session->internals.selected_need_free != 0)
    {
      int i;

      for (i = 0; i < session->internals.selected_cert_list_length; i++)
        {
          _gnutls_gcert_deinit (&session->internals.selected_cert_list[i]);
        }
      gnutls_free (session->internals.selected_cert_list);
      session->internals.selected_cert_list = NULL;
      session->internals.selected_cert_list_length = 0;

      gnutls_privkey_deinit(session->internals.selected_key);
      session->internals.selected_key = NULL;
    }

  return;
}
