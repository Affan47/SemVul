guestfs_session_e2fsck(GuestfsSession *session, const gchar *device, GuestfsE2fsck *optargs, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "e2fsck");
    return FALSE;
  }

  struct guestfs_e2fsck_argv argv;
  struct guestfs_e2fsck_argv *argvp = NULL;

  if (optargs) {
    argv.bitmask = 0;

    GValue correct_v = {0, };
    g_value_init(&correct_v, GUESTFS_TYPE_TRISTATE);
    g_object_get_property(G_OBJECT(optargs), "correct", &correct_v);
    GuestfsTristate correct = g_value_get_enum(&correct_v);
    if (correct != GUESTFS_TRISTATE_NONE) {
      argv.bitmask |= GUESTFS_E2FSCK_CORRECT_BITMASK;
      argv.correct = correct;
    }
    GValue forceall_v = {0, };
    g_value_init(&forceall_v, GUESTFS_TYPE_TRISTATE);
    g_object_get_property(G_OBJECT(optargs), "forceall", &forceall_v);
    GuestfsTristate forceall = g_value_get_enum(&forceall_v);
    if (forceall != GUESTFS_TRISTATE_NONE) {
      argv.bitmask |= GUESTFS_E2FSCK_FORCEALL_BITMASK;
      argv.forceall = forceall;
    }
    argvp = &argv;
  }
  int ret = guestfs_e2fsck_argv (g, device, argvp);
  if (ret == -1) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return FALSE;
  }

  return TRUE;
}
