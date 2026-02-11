sp_writer_accept_client (ShmPipe * self)
{
  ShmClient *client = NULL;
  int fd;
  struct CommandBuffer cb = { 0 };
  int pathlen = strlen (self->shm_area->shm_area_name) + 1;


  fd = accept (self->main_socket, NULL, NULL);

  if (fd < 0) {
    fprintf (stderr, "Could not client connection");
    return NULL;
  }

  cb.payload.new_shm_area.size = self->shm_area->shm_area_len;
  cb.payload.new_shm_area.path_size = pathlen;
  if (!send_command (fd, &cb, COMMAND_NEW_SHM_AREA, self->shm_area->id)) {
    fprintf (stderr, "Sending new shm area failed: %s", strerror (errno));
    goto error;
  }

  if (send (fd, self->shm_area->shm_area_name, pathlen, MSG_NOSIGNAL) !=
      pathlen) {
    fprintf (stderr, "Sending new shm area path failed: %s", strerror (errno));
    goto error;
  }

  client = spalloc_new (ShmClient);
  client->fd = fd;


  client->next = self->clients;
  self->clients = client;
  self->num_clients++;

  return client;

error:
  close (fd);
  return NULL;
}
