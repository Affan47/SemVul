send_command (int fd, struct CommandBuffer *cb, unsigned short int type,
    int area_id)
{
  cb->type = type;
  cb->area_id = area_id;

  if (send (fd, cb, sizeof (struct CommandBuffer), MSG_NOSIGNAL) !=
      sizeof (struct CommandBuffer))
    return 0;

  return 1;
}
