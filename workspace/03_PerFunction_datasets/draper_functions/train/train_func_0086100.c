mbox_mailstorage_init(struct mailstorage * storage,
    const char * mbox_pathname, int mbox_cached,
    const char * mbox_cache_directory, const char * mbox_flags_directory)
{
  struct mbox_mailstorage * mbox_storage;

  mbox_storage = malloc(sizeof(* mbox_storage));
  if (mbox_storage == NULL)
    goto err;

  mbox_storage->mbox_pathname = strdup(mbox_pathname);
  if (mbox_storage->mbox_pathname == NULL)
    goto free;

  mbox_storage->mbox_cached = mbox_cached;

  if (mbox_cached && (mbox_cache_directory != NULL) &&
      (mbox_flags_directory != NULL)) {
    mbox_storage->mbox_cache_directory = strdup(mbox_cache_directory);
    if (mbox_storage->mbox_cache_directory == NULL)
      goto free_pathname;

    mbox_storage->mbox_flags_directory = strdup(mbox_flags_directory);
    if (mbox_storage->mbox_flags_directory == NULL)
      goto free_cache_directory;
  }
  else {
    mbox_storage->mbox_cached = FALSE;
    mbox_storage->mbox_cache_directory = NULL;
    mbox_storage->mbox_flags_directory = NULL;
  }

  storage->sto_data = mbox_storage;
  storage->sto_driver = &mbox_mailstorage_driver;

  return MAIL_NO_ERROR;

 free_cache_directory:
  free(mbox_storage->mbox_cache_directory);
 free_pathname:
  free(mbox_storage->mbox_pathname);
 free:
  free(mbox_storage);
 err:
  return MAIL_ERROR_MEMORY;
}
