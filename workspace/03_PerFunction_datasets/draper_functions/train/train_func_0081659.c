claws_mailmbox_folder_new(const char * mb_filename)
{
  struct claws_mailmbox_folder * folder;

  folder = malloc(sizeof(* folder));
  if (folder == NULL)
    goto err;

  strncpy(folder->mb_filename, mb_filename, PATH_MAX);

  folder->mb_mtime = (time_t) -1;

  folder->mb_fd = -1;
  folder->mb_read_only = TRUE;
  folder->mb_no_uid = TRUE;

  folder->mb_changed = FALSE;
  folder->mb_deleted_count = 0;

  folder->mb_mapping = NULL;
  folder->mb_mapping_size = 0;

  folder->mb_written_uid = 0;
  folder->mb_max_uid = 0;

  folder->mb_hash = chash_new(CHASH_DEFAULTSIZE, CHASH_COPYKEY);
  if (folder->mb_hash == NULL)
    goto free;

  folder->mb_tab = carray_new(128);
  if (folder->mb_tab == NULL)
    goto free_hash;

  return folder;

 free_hash:
  chash_free(folder->mb_hash);
 free:
  free(folder);
 err:
  return NULL;
}
