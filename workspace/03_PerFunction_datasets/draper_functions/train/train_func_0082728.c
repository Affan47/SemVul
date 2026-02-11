clear_filebrowser_backend(FilebrowserBackendDetails *directory, gboolean clear_current_folder){
  if (directory->filesinfolder) g_slist_free (directory->filesinfolder);
  directory->filesinfolder=NULL;
  if (directory->current_folder && clear_current_folder){
    g_free(directory->current_folder);
    directory->current_folder=NULL;
  }
}
