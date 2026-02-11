guestfs_session_internal_test_rstructerr(GuestfsSession *session, GError **err)
{
  guestfs_h *g = session->priv->g;
  if (g == NULL) {
    g_set_error(err, GUESTFS_ERROR, 0,
                "attempt to call %s after the session has been closed",
                "internal_test_rstructerr");
    return NULL;
  }

  struct guestfs_lvm_pv *ret = guestfs_internal_test_rstructerr (g);
  if (ret == NULL) {
    g_set_error_literal(err, GUESTFS_ERROR, 0, guestfs_last_error(g));
    return NULL;
  }

  GuestfsPV *s = g_slice_new0(GuestfsPV);
  if (ret->pv_name) s->pv_name = g_strdup(ret->pv_name);
  if (ret->pv_uuid) memcpy(s->pv_uuid, ret->pv_uuid, sizeof(s->pv_uuid));
  if (ret->pv_fmt) s->pv_fmt = g_strdup(ret->pv_fmt);
  s->pv_size = ret->pv_size;
  s->dev_size = ret->dev_size;
  s->pv_free = ret->pv_free;
  s->pv_used = ret->pv_used;
  if (ret->pv_attr) s->pv_attr = g_strdup(ret->pv_attr);
  s->pv_pe_count = ret->pv_pe_count;
  s->pv_pe_alloc_count = ret->pv_pe_alloc_count;
  if (ret->pv_tags) s->pv_tags = g_strdup(ret->pv_tags);
  s->pe_start = ret->pe_start;
  s->pv_mda_count = ret->pv_mda_count;
  s->pv_mda_free = ret->pv_mda_free;
  guestfs_free_lvm_pv(ret);
  return s;
}
