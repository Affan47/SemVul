socket_data_new(int fd)
{
  struct mailstream_socket_data * socket_data;

  socket_data = (struct mailstream_socket_data * ) malloc(sizeof(* socket_data));
  if (socket_data == NULL)
    goto err;

  socket_data->fd = fd;
  socket_data->cancel = mailstream_cancel_new();
  if (socket_data->cancel == NULL)
    goto free;

  return socket_data;

 free:
  free(socket_data);
 err:
  return NULL;
}
