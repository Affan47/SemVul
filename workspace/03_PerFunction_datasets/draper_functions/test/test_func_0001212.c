transfer_payload_headers (GstCurlSmtpSink * sink,
    void *curl_ptr, size_t block_size)
{
  size_t bytes_to_send;
  GByteArray *headers = sink->payload_headers;

  bytes_to_send = MIN (block_size, headers->len);
  memcpy ((guint8 *) curl_ptr, headers->data, bytes_to_send);
  g_byte_array_remove_range (headers, 0, bytes_to_send);


  if (headers->len == 0) {
    g_byte_array_free (headers, TRUE);
    sink->payload_headers = NULL;
  }

  return bytes_to_send;
}
