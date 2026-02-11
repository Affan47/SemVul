unappend_request (GDaemonFileInputStream *stream)
{
  g_assert (stream->output_buffer->len >= G_VFS_DAEMON_SOCKET_PROTOCOL_REQUEST_SIZE);

  stream->seq_nr--;
  g_string_truncate (stream->output_buffer,
		     stream->output_buffer->len - G_VFS_DAEMON_SOCKET_PROTOCOL_REQUEST_SIZE);
}
