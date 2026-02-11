prefetch(mailmessage * msg_info)
{
  struct generic_message_t * msg;
  int res;
  struct maildir_msg_data * data;
  char * filename;
  int fd;
  char * mapping;
  struct maildir * md;

  md = get_maildir_session(msg_info);

  filename = maildir_message_get(md, msg_info->msg_uid);
  if (filename == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto err;
  }

  fd = open(filename, O_RDONLY);
  free(filename);
  if (fd == -1) {
    res = MAIL_ERROR_FILE;
    goto err;
  }

  mapping = mmap(NULL, msg_info->msg_size, PROT_READ, MAP_PRIVATE, fd, 0);
  if (mapping == (char *)MAP_FAILED) {
    res = MAIL_ERROR_FILE;
    goto close;
  }

  data = malloc(sizeof(* data));
  if (data == NULL) {
    res = MAIL_ERROR_MEMORY;
    goto unmap;
  }

  data->fd = fd;

  msg = msg_info->msg_data;

  msg->msg_data = data;
  msg->msg_message = mapping;
  msg->msg_length = msg_info->msg_size;

  return MAIL_NO_ERROR;

 unmap:
  munmap(mapping, msg_info->msg_size);
 close:
  close(fd);
 err:
  return res;
}
