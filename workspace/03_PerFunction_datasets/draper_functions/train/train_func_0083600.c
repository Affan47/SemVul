_gnutls_buffer_pop_data_prefix (gnutls_buffer_st * buf, void *data,
                                size_t * data_size)
{
  size_t size;
  int ret;

  ret = _gnutls_buffer_pop_prefix (buf, &size, 1);
  if (ret < 0)
    {
      gnutls_assert ();
      return ret;
    }

  if (size > 0)
    _gnutls_buffer_pop_data (buf, data, data_size);

  return 0;
}
