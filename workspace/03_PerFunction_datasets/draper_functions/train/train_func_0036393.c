_gnutls_write_datum16 (opaque * dest, gnutls_datum_t dat)
{
  _gnutls_write_uint16 (dat.size, dest);
  if (dat.data != NULL)
    memcpy (&dest[2], dat.data, dat.size);
}
