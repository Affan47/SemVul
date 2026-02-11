pkt_write_head (cdk_stream_t out, int old_ctb, size_t size, int type)
{
  if (old_ctb)
    return write_head_old (out, size, type);
  return write_head_new (out, size, type);
}
