mailmh_folder_remove_message(struct mailmh_folder * folder,
				 uint32_t indx)
{
  char * filename;
  struct mailmh_msg_info * msg_info;
  int res;
  int r;
  chashdatum key;
  chashdatum data;

  r = mailmh_folder_get_message_filename(folder, indx, &filename);
  if (filename == NULL) {
    res = r;
    goto err;
  }

  if (unlink(filename) == -1) {
    res = MAILMH_ERROR_FILE;
    goto free;
  }

  key.data = &indx;
  key.len = sizeof(indx);
  r = chash_get(folder->fl_msgs_hash, &key, &data);
  if (r == 0) {
    msg_info = data.data;

    carray_delete_fast(folder->fl_msgs_tab, msg_info->msg_array_index);
    chash_delete(folder->fl_msgs_hash, &key, NULL);
  }

  return MAILMH_NO_ERROR;

 free:
  free(filename);
 err:
  return res;
}
