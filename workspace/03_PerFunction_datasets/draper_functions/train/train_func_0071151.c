zxid_simple_ab_pep(zxid_conf* cf, zxid_ses* ses, int* res_len, int auto_flags)
{
  char* res;
  struct zx_str* ss;
  D_INDENT("ab_pep: ");
  DD("ab_pep %d", 0);
  zxid_ses_to_pool(cf, ses);

  if (!zxid_localpdp(cf, ses)) {
    DD("Deny by local PDP %d",0);
    D_DEDENT("ab_pep: ");
    return "z";
  }

  if (cf->pdp_url && *cf->pdp_url) {


    if (!zxid_pep_az_soap_pepmap(cf, 0, ses, cf->pdp_url, cf->pepmap, "sso az")) {
      INFO("DENY by remote PDP %d", 0);
      D_DEDENT("ab_pep: ");
      return "z";
    }
  }

  switch (auto_flags & (ZXID_AUTO_FMTQ | ZXID_AUTO_FMTJ)) {
  case ZXID_AUTO_FMTQ|ZXID_AUTO_FMTJ: ss = zx_dup_str(cf->ctx, ""); break;
  case ZXID_AUTO_FMTQ:  ss = zxid_ses_to_qs(cf, ses); break;
  case ZXID_AUTO_FMTJ:  ss = zxid_ses_to_json(cf, ses); break;
  default: ERR("Unsupported output format bits %x", auto_flags & (ZXID_AUTO_FMTQ|ZXID_AUTO_FMTJ));
  case 0:               ss = zxid_ses_to_ldif(cf, ses); break;
  }
  if (zx_debug & ZXID_INOUT)
    INFO("LDIF(%.*s)", ss?ss->len:1, ss?ss->s:"-");
  if (cf->log_level > 0)
    zxlog(cf, 0,0,0,0,0,0, ZX_GET_CONTENT(ses->nameid), "N", "K", "SHOWPC", ses->sid, 0);
  res = ss->s;
  if (res_len)
    *res_len = ss->len;
  ZX_FREE(cf->ctx, ss);
  D_DEDENT("ab_pep: ");
  return res;
}
