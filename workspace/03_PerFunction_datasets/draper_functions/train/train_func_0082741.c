_gnutls_buffer_resize (gnutls_buffer_st * dest, size_t new_size)
{
  if (dest->max_length >= new_size)
    {
      size_t unused = MEMSUB (dest->data, dest->allocd);
      if (dest->max_length - unused <= new_size)
        {
          if (dest->length && dest->data)
            memmove (dest->allocd, dest->data, dest->length);
          dest->data = dest->allocd;
        }

      return 0;
    }
  else
    {
      size_t unused = MEMSUB (dest->data, dest->allocd);
      size_t alloc_len =
        MAX (new_size, MIN_CHUNK) + MAX (dest->max_length, MIN_CHUNK);

      dest->allocd = gnutls_realloc (dest->allocd, alloc_len);
      if (dest->allocd == NULL)
        {
          gnutls_assert ();
          return GNUTLS_E_MEMORY_ERROR;
        }
      dest->max_length = alloc_len;
      dest->data = dest->allocd + unused;

      if (dest->length && dest->data)
        memmove (dest->allocd, dest->data, dest->length);
      dest->data = dest->allocd;

      return 0;
    }
}
