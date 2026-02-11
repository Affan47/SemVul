mailmh_folder_add_message_uid(struct mailmh_folder * folder,
    const char * message, size_t size,
    uint32_t * pindex)
{
  char * tmpname;
  int fd;
  size_t namesize;
  size_t left;
  ssize_t res;
  struct mailmh_msg_info * msg_info;
  uint32_t indx;
  int error;
  int r;
  unsigned int array_index;
  struct stat buf;
  chashdatum key;
  chashdatum data;

  namesize = strlen(folder->fl_filename) + 20;
  tmpname = malloc(namesize);
  snprintf(tmpname, namesize, "%s%ctmpXXXXXX",
	   folder->fl_filename, MAIL_DIR_SEPARATOR);
  fd = mkstemp(tmpname);
  if (fd < 0) {
    error = MAILMH_ERROR_FILE;
    goto free;
  }

  left = size;
  while (left > 0) {
    res = write(fd, message, left);
    if (res == -1) {
      close(fd);
      error = MAILMH_ERROR_FILE;
      goto free;
    }

    left -= res;
  }
  close(fd);

  r = stat(tmpname, &buf);
  if (r < 0) {
    error = MAILMH_ERROR_FILE;
    goto free;
  }

  r = mailmh_folder_alloc_msg(folder, tmpname, &indx);
  if (r != MAILMH_NO_ERROR) {
    unlink(tmpname);
    error = MAILMH_ERROR_COULD_NOT_ALLOC_MSG;
    goto free;
  }
  free(tmpname);

  msg_info = mailmh_msg_info_new(indx, size, buf.st_mtime);
  if (msg_info == NULL) {
    mailmh_folder_remove_message(folder, indx);
    error = MAILMH_ERROR_MEMORY;
    goto err;
  }

  r = carray_add(folder->fl_msgs_tab, msg_info, &array_index);
  if (r < 0) {
    mailmh_folder_remove_message(folder, indx);
    mailmh_msg_info_free(msg_info);
    error = MAILMH_ERROR_MEMORY;
    goto err;
  }
  msg_info->msg_array_index = array_index;

  key.data = &indx;
  key.len = sizeof(indx);
  data.data = msg_info;
  data.len = 0;

  if (pindex != NULL)
    * pindex = indx;

  r = chash_set(folder->fl_msgs_hash, &key, &data, NULL);
  if (r < 0) {
    carray_delete_fast(folder->fl_msgs_tab, msg_info->msg_array_index);
    mailmh_msg_info_free(msg_info);
    error = MAILMH_ERROR_MEMORY;
    goto err;
  }

  return MAILMH_NO_ERROR;

 free:
  free(tmpname);
 err:
  return error;
}
