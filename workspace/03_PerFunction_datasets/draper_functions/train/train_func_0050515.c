g_vfs_afp_command_set_buffer (GVfsAfpCommand *comm, char *buf, gsize size)
{
  g_return_if_fail (buf != NULL);
  g_return_if_fail (size > 0);

  comm->buf = buf;
  comm->buf_size = size;
}
