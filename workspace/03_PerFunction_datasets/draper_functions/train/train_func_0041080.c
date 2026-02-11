_gnutls_extension_list_check (gnutls_session_t session, uint16_t type)
{
  if (session->security_parameters.entity == GNUTLS_CLIENT)
    {
      int i;

      for (i = 0; i < session->internals.extensions_sent_size; i++)
        {
          if (type == session->internals.extensions_sent[i])
            return 0;
        }

      return GNUTLS_E_RECEIVED_ILLEGAL_EXTENSION;
    }

  return 0;
}
