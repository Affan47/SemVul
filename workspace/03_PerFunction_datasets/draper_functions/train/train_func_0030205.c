gnutls_dh_get_peers_public_bits (gnutls_session_t session)
{
  dh_info_st *dh;

  switch (gnutls_auth_get_type (session))
    {
    case GNUTLS_CRD_ANON:
      {
        anon_auth_info_t info;

        info = _gnutls_get_auth_info (session);
        if (info == NULL)
          return GNUTLS_E_INTERNAL_ERROR;

        dh = &info->dh;
        break;
      }
    case GNUTLS_CRD_PSK:
      {
        psk_auth_info_t info;

        info = _gnutls_get_auth_info (session);
        if (info == NULL)
          return GNUTLS_E_INTERNAL_ERROR;

        dh = &info->dh;
        break;
      }
    case GNUTLS_CRD_CERTIFICATE:
      {
        cert_auth_info_t info;

        info = _gnutls_get_auth_info (session);
        if (info == NULL)
          return GNUTLS_E_INTERNAL_ERROR;

        dh = &info->dh;
        break;
      }
    default:
      gnutls_assert ();
      return GNUTLS_E_INVALID_REQUEST;
    }

  return mpi_buf2bits (&dh->public_key);
}
