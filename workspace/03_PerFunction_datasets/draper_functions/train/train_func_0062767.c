guestfs_session_inotify_read(GuestfsSession *session, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "inotify_read");
    return NULL;
  }

  struct guestfs_inotify_event_list *ret = guestfs_inotify_read (g);
  if (ret == NULL) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return NULL;
  }

  GuestfsINotifyEvent **l = g_malloc(sizeof(GuestfsINotifyEvent*) * (ret->len + 1));
  gsize i;
  for (i = 0; i < ret->len; i++) {
    l[i] = g_slice_new0(GuestfsINotifyEvent);
    l[i]->in_wd = ret->val[i].in_wd;
    l[i]->in_mask = ret->val[i].in_mask;
    l[i]->in_cookie = ret->val[i].in_cookie;
    if (ret->val[i].in_name) l[i]->in_name = g_strdup(ret->val[i].in_name);
  }
  guestfs_free_inotify_event_list(ret);
  l[i] = NULL;
  return l;
}
