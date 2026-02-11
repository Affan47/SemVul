cdk_stream_enable_cache (cdk_stream_t s, int val)
{
  if (!s)
    {
      gnutls_assert ();
      return CDK_Inv_Value;
    }
  if (!s->flags.write)
    {
      gnutls_assert ();
      return CDK_Inv_Mode;
    }
  s->cache.on = val;
  if (!s->cache.buf)
    {
      s->cache.buf = cdk_calloc (1, STREAM_BUFSIZE);
      s->cache.alloced = STREAM_BUFSIZE;
      _gnutls_read_log ("stream: allocate cache of %d octets\n",
                        STREAM_BUFSIZE);
    }
  return 0;
}
