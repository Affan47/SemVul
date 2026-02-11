ds_fopen_secure(const char *path, const char *mode, size_t size)
{
  FILE *fp;
  Ds *buffer;

  if ((fp = fopen(path, mode)) == NULL)
	return(NULL);

  buffer = ds_init_size(NULL, size);
  buffer->clear_flag = 1;
  setbuffer(fp, ds_buf(buffer), size);

  stream_add(fp, buffer);

  return(fp);
}
