_gnutls_get_auth_info_gcert (gnutls_cert * gcert,
                             gnutls_certificate_type_t type,
                             cert_auth_info_t info,
                             int flags  )
{
  switch (type)
    {
    case GNUTLS_CRT_X509:
      return _gnutls_x509_raw_cert_to_gcert (gcert,
                                             &info->raw_certificate_list[0],
                                             flags);
#ifdef ENABLE_OPENPGP
    case GNUTLS_CRT_OPENPGP:
      return _gnutls_openpgp_raw_crt_to_gcert (gcert,
                                               &info->raw_certificate_list[0],
                                               info->use_subkey ? info->
                                               subkey_id : NULL);
#endif
    default:
      gnutls_assert ();
      return GNUTLS_E_INTERNAL_ERROR;
    }
}
