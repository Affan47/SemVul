_ds_shutdown_storage (DSPAM_CTX * CTX)
{
  struct _hash_drv_storage *s;
  struct nt_node *node_nt;
  struct nt_c c_nt;

  if (!CTX || !CTX->storage)
    return EINVAL;

  s  = (struct _hash_drv_storage *) CTX->storage;


  node_nt = c_nt_first (s->dir_handles, &c_nt);
  while (node_nt != NULL)
  {
    DIR *dir;
    dir = (DIR *) node_nt->ptr;
    closedir (dir);
    node_nt = c_nt_next (s->dir_handles, &c_nt);
  }
  nt_destroy (s->dir_handles);

  if (CTX->operating_mode != DSM_CLASSIFY)
    _hash_drv_set_spamtotals (CTX);


  if (!s->dbh_attached) {
    _hash_drv_close(s->map);
    free(s->map);
    int lock_result =
      _hash_drv_lock_free (s, (CTX->group) ? CTX->group : CTX->username);
    if (lock_result < 0)
      return EUNKNOWN;
  }

  free (CTX->storage);
  CTX->storage = NULL;

  return 0;
}
