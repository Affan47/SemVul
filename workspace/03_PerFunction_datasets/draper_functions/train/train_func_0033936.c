_gnutls_handshake_io_cache_int (gnutls_session_t session,
                                gnutls_handshake_description_t htype,
                                mbuffer_st * bufel)
{
  mbuffer_head_st *const send_buffer =
    &session->internals.handshake_send_buffer;

  _mbuffer_enqueue (send_buffer, bufel);
  session->internals.handshake_send_buffer_htype = htype;

  _gnutls_write_log
    ("HWRITE: enqueued %d. Total %d bytes.\n",
     (int) bufel->msg.size, (int) send_buffer->byte_length);

  return;
}
