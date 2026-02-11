mailmh_folder_rename_subfolder(struct mailmh_folder * src_folder,
				   struct mailmh_folder * dst_folder,
				   const char * new_name)
{
  int r;
  struct mailmh_folder * folder;
  struct mailmh_folder * parent;
  char * new_foldername;

  parent = src_folder->fl_parent;
  if (parent == NULL)
    return MAILMH_ERROR_RENAME;

  new_foldername = malloc(strlen(dst_folder->fl_filename) + 2 + strlen(new_name));
  if (new_foldername == NULL)
    return MAILMH_ERROR_MEMORY;

  strcpy(new_foldername, dst_folder->fl_filename);
  strcat(new_foldername, MAIL_DIR_SEPARATOR_S);
  strcat(new_foldername, new_name);

  r = rename(src_folder->fl_filename, new_foldername);
  free(new_foldername);
  if (r < 0)
    return MAILMH_ERROR_RENAME;

  r = mailmh_folder_remove_subfolder(src_folder);
  if (r != MAILMH_NO_ERROR)
    return r;

  folder = mailmh_folder_new(dst_folder, new_name);
  if (folder == NULL)
    return MAILMH_ERROR_MEMORY;

  r = carray_add(parent->fl_subfolders_tab, folder, NULL);
  if (r < 0) {
    mailmh_folder_free(folder);
    return MAILMH_ERROR_MEMORY;
  }

  return MAILMH_NO_ERROR;
}
