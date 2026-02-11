es_opaque_set (estream_t stream, void *opaque)
{
  ESTREAM_LOCK (stream);
  es_opaque_ctrl (stream, opaque, NULL);
  ESTREAM_UNLOCK (stream);
}
