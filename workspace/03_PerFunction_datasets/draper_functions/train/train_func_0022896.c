_gnutls_buffer_unescape (gnutls_buffer_st * dest)
{
  int rv = -1;
  int pos = 0;

  while (pos < dest->length)
    {
      if (dest->data[pos] == '%')
        {
          char b[3];
          unsigned int u;
          unsigned char x;

          b[0] = dest->data[pos + 1];
          b[1] = dest->data[pos + 2];
          b[2] = 0;

          sscanf (b, "%02x", &u);

          x = u;

          _gnutls_buffer_delete_data (dest, pos, 3);
          _gnutls_buffer_insert_data (dest, pos, &x, 1);
        }
      pos++;
    }

  rv = 0;

  return rv;
}
