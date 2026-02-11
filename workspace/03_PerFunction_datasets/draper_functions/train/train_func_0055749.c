gnutls_x509_privkey_cpy (gnutls_x509_privkey_t dst, gnutls_x509_privkey_t src)
{
  int i, ret;

  if (!src || !dst)
    return GNUTLS_E_INVALID_REQUEST;

  for (i = 0; i < src->params_size; i++)
    {
      dst->params[i] = _gnutls_mpi_copy (src->params[i]);
      if (dst->params[i] == NULL)
        return GNUTLS_E_MEMORY_ERROR;
    }

  dst->params_size = src->params_size;
  dst->pk_algorithm = src->pk_algorithm;

  switch (dst->pk_algorithm)
    {
        case GNUTLS_PK_DSA:
          ret = _gnutls_asn1_encode_dsa (&dst->key, dst->params);
          if (ret < 0)
            {
              gnutls_assert ();
              return ret;
            }
          break;
        case GNUTLS_PK_RSA:
          ret = _gnutls_asn1_encode_rsa (&dst->key, dst->params);
          if (ret < 0)
            {
              gnutls_assert ();
              return ret;
            }
          break;
        default:
          gnutls_assert ();
          return GNUTLS_E_INVALID_REQUEST;
    }

  return 0;
}
