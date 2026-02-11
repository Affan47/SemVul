zxid_sp_oauth2_dispatch(zxid_conf* cf, zxid_cgi* cgi, zxid_ses* ses)
{
  int ret;

  if (cgi->id_token) {
    ret = zxid_sp_dig_oauth_sso_a7n(cf, cgi, ses);
    D("ret=%d ses=%p", ret, ses);
    switch (ret) {
    case ZXID_OK:      return zx_dup_str(cf->ctx, "K");
    case ZXID_SSO_OK:  return zx_dup_str(cf->ctx, "O");
    case ZXID_IDP_REQ:
      return zx_dup_str(cf->ctx, zxid_simple_ses_active_cf(cf, cgi, ses, 0, 0x1fff));
    case ZXID_FAIL:
      D("*** FAIL, should send back to IdP select %d", 0);
      return zx_dup_str(cf->ctx, "* ERR");
    }
    return zx_dup_str(cf->ctx, "M");
  }

  if (cf->log_level > 0)
    zxlog(cf, 0, 0, 0, 0, 0, 0, ZX_GET_CONTENT(ses->nameid), "N", "C", "SPOADISP", 0, "sid(%s) unknown req or resp", STRNULLCHK(ses->sid));
  ERR("Unknown request or response %d", 0);
  return zx_dup_str(cf->ctx, "* ERR");
}
