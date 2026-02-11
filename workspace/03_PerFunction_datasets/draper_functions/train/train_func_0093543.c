read_cb(void *cookie, char *buf, size_t n)
{
  URL_FILE *file = (URL_FILE*)cookie;


  if (wait_for_data(file, n) != CURLM_OK) {errno = EIO; return -1;}

  if (file->buffer_pos < n) n = file->buffer_pos;
  if (!buf) {errno = EFAULT; return -1;}
  memcpy(buf, file->buffer, n);
  file->buffer_pos -= n;
  memmove(file->buffer, file->buffer + n, file->buffer_pos);
  return n;
}
