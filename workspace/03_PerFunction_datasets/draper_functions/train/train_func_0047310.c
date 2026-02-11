stream_read (cdk_stream_t s, void *buf, size_t buflen, size_t * r_nread)
{
  *r_nread = cdk_stream_read (s, buf, buflen);
  return *r_nread > 0 ? 0 : _cdk_stream_get_errno (s);
}
