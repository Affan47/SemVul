guestfs_session_lstatlist(GuestfsSession *session, const gchar *path, gchar *const *names, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "lstatlist");
    return NULL;
  }

  struct guestfs_stat_list *ret = guestfs_lstatlist (g, path, names);
  if (ret == NULL) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return NULL;
  }

  GuestfsStat **l = g_malloc(sizeof(GuestfsStat*) * (ret->len + 1));
  gsize i;
  for (i = 0; i < ret->len; i++) {
    l[i] = g_slice_new0(GuestfsStat);
    l[i]->dev = ret->val[i].dev;
    l[i]->ino = ret->val[i].ino;
    l[i]->mode = ret->val[i].mode;
    l[i]->nlink = ret->val[i].nlink;
    l[i]->uid = ret->val[i].uid;
    l[i]->gid = ret->val[i].gid;
    l[i]->rdev = ret->val[i].rdev;
    l[i]->size = ret->val[i].size;
    l[i]->blksize = ret->val[i].blksize;
    l[i]->blocks = ret->val[i].blocks;
    l[i]->atime = ret->val[i].atime;
    l[i]->mtime = ret->val[i].mtime;
    l[i]->ctime = ret->val[i].ctime;
  }
  guestfs_free_stat_list(ret);
  l[i] = NULL;
  return l;
}
