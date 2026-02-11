mailmime_data_write_driver(int (* do_write)(void *, const char *, size_t), void * data, int * col,
    struct mailmime_data * mime_data,
    int istext)
{
  int fd;
  int r;
  char * text;
  struct stat buf;
  int res;

  switch (mime_data->dt_type) {
  case MAILMIME_DATA_TEXT:

    if (mime_data->dt_encoded) {
      r = mailimf_string_write_driver(do_write, data, col,
          mime_data->dt_data.dt_text.dt_data,
          mime_data->dt_data.dt_text.dt_length);
      if (r != MAILIMF_NO_ERROR)
	return r;
    }
    else {
      r = mailmime_text_content_write_driver(do_write, data, col, mime_data->dt_encoding, istext,
          mime_data->dt_data.dt_text.dt_data,
          mime_data->dt_data.dt_text.dt_length);
      if (r != MAILIMF_NO_ERROR)
	return r;
    }

    break;

  case MAILMIME_DATA_FILE:
    fd = open(mime_data->dt_data.dt_filename, O_RDONLY);
    if (fd < 0) {
      res = MAILIMF_ERROR_FILE;
      goto err;
    }

    r = fstat(fd, &buf);
    if (r < 0) {
      res = MAILIMF_ERROR_FILE;
      goto close;
    }

    if (buf.st_size != 0) {
      text = mmap(NULL, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0);
      if (text == (char *)MAP_FAILED) {
	res = MAILIMF_ERROR_FILE;
	goto close;
      }

      if (mime_data->dt_encoded) {
	r = mailimf_string_write_driver(do_write, data, col, text, buf.st_size);
	if (r != MAILIMF_NO_ERROR) {
	  res = r;
          goto unmap;
        }
      }
      else {
	r = mailmime_text_content_write_driver(do_write, data, col, mime_data->dt_encoding, istext,
            text, buf.st_size);
	if (r != MAILIMF_NO_ERROR) {
	  res = r;
          goto unmap;
        }
      }

      munmap(text, buf.st_size);
    }
    close(fd);

    if (r != MAILIMF_NO_ERROR)
      return r;

    break;

  unmap:
    munmap(text, buf.st_size);
  close:
    close(fd);
  err:
    return res;
  }

  return MAILIMF_NO_ERROR;
}
