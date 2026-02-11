gnutls_pem_base64_encode_alloc (const char *msg,
                                const gnutls_datum_t * data,
                                gnutls_datum_t * result)
{
  opaque *ret;
  int size;

  if (result == NULL)
    return GNUTLS_E_INVALID_REQUEST;

  size = _gnutls_fbase64_encode (msg, data->data, data->size, &ret);
  if (size < 0)
    return size;

  result->data = ret;
  result->size = size - 1;
  return 0;
}
