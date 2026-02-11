handle_get_quad_freq (fs_backend *be, fs_segment segment,
                                             unsigned int length,
                                             unsigned char *content)
{
  if (segment > be->segments) {
    fs_error(LOG_ERR, "invalid segment number: %d", segment);
    return fsp_error_new(segment, "invalid segment number");
  }

  if (length != 8) {
    fs_error(LOG_ERR, "get_quad_freq(%d) wrong length %u", segment, length);
    return fsp_error_new(segment, "wrong length");
  }

  int index, count;
  memcpy(&index, content, sizeof(int));
  memcpy(&count, content + sizeof(int), sizeof(int));

  const char *filename;


  filename = "";
  int fd = open(filename, FS_O_NOATIME | O_RDONLY, 0);
  unsigned char *reply =  message_new(FS_QUAD_FREQ, segment, count * sizeof(fs_quad_freq));

  ssize_t bytes = 0;

  unsigned int *l = (unsigned int *) (reply + 4);
  *l = bytes;
  close(fd);

  return reply;
}
