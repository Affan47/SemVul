guestfs_session_xfs_info(GuestfsSession *session, const gchar *pathordevice, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "xfs_info");
    return NULL;
  }

  struct guestfs_xfsinfo *ret = guestfs_xfs_info (g, pathordevice);
  if (ret == NULL) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return NULL;
  }

  GuestfsXFSInfo *s = g_slice_new0(GuestfsXFSInfo);
  if (ret->xfs_mntpoint) s->xfs_mntpoint = g_strdup(ret->xfs_mntpoint);
  s->xfs_inodesize = ret->xfs_inodesize;
  s->xfs_agcount = ret->xfs_agcount;
  s->xfs_agsize = ret->xfs_agsize;
  s->xfs_sectsize = ret->xfs_sectsize;
  s->xfs_attr = ret->xfs_attr;
  s->xfs_blocksize = ret->xfs_blocksize;
  s->xfs_datablocks = ret->xfs_datablocks;
  s->xfs_imaxpct = ret->xfs_imaxpct;
  s->xfs_sunit = ret->xfs_sunit;
  s->xfs_swidth = ret->xfs_swidth;
  s->xfs_dirversion = ret->xfs_dirversion;
  s->xfs_dirblocksize = ret->xfs_dirblocksize;
  s->xfs_cimode = ret->xfs_cimode;
  if (ret->xfs_logname) s->xfs_logname = g_strdup(ret->xfs_logname);
  s->xfs_logblocksize = ret->xfs_logblocksize;
  s->xfs_logblocks = ret->xfs_logblocks;
  s->xfs_logversion = ret->xfs_logversion;
  s->xfs_logsectsize = ret->xfs_logsectsize;
  s->xfs_logsunit = ret->xfs_logsunit;
  s->xfs_lazycount = ret->xfs_lazycount;
  if (ret->xfs_rtname) s->xfs_rtname = g_strdup(ret->xfs_rtname);
  s->xfs_rtextsize = ret->xfs_rtextsize;
  s->xfs_rtblocks = ret->xfs_rtblocks;
  s->xfs_rtextents = ret->xfs_rtextents;
  guestfs_free_xfsinfo(ret);
  return s;
}
