mailmh_folder_remove_subfolder(struct mailmh_folder * folder)
{
  struct mailmh_folder * parent;
  chashdatum key;
  chashdatum data;
  int r;

  parent = folder->fl_parent;

  key.data = folder->fl_filename;
  key.len = strlen(folder->fl_filename);

  r = chash_get(parent->fl_subfolders_hash, &key, &data);
  if (r < 0)
    return MAILMH_ERROR_FOLDER;

  chash_delete(parent->fl_subfolders_hash, &key, NULL);
  carray_delete_fast(parent->fl_subfolders_tab, folder->fl_array_index);

  mailmh_folder_free(folder);

  return MAILMH_NO_ERROR;

}
