zxid_wsp_validate(zxid_conf* cf, zxid_ses* ses, const char* az_cred, const char* enve)
{
  struct zx_str  ss;
  char* p;
  char msg[256];
  struct zx_str* logpath;
  struct zx_root_s* r;

  if (!cf || !ses || !enve) {
    ERR("Missing config, session, or envelope argument %p %p %p (programmer error)", cf,ses,enve);
    return 0;
  }
  ss.s = (char*)enve;
  ss.len = strlen(enve);
  D_XML_BLOB(cf, "WSP_VALIDATE", ss.len, ss.s);
  r = zx_dec_zx_root(cf->ctx, ss.len, enve, "valid");
  if (!r) {
    zx_format_parse_error(cf->ctx, msg, sizeof(msg), "valid");
    ERR("Malformed XML: %s", msg);

    for (p = msg; *p; ++p)
      if (*p == '"')
	*p = '\'';
    zxid_set_fault(cf, ses, zxid_mk_fault(cf, 0, TAS3_PEP_RQ_IN, "e:Client", "Malformed XML", "IDStarMsgNotUnderstood", 0, msg, 0));
    return 0;
  }
  p = zxid_wsp_validate_env(cf, ses, az_cred, r->Envelope);
  ZX_FREE(cf->ctx, r);

  logpath = zxlog_path(cf, ses->issuer, ses->wsp_msgid, ZXLOG_RELY_DIR, ZXLOG_MSG_KIND, 1);
  if (!logpath) {
    ERR("Log path not valid, empty issuer? %p %p", ses->issuer, ses->wsp_msgid);
    return 0;
  }
  if (zxlog_dup_check(cf, logpath, "validate request")) {
    if (cf->dup_msg_fatal) {
      zxlog_blob(cf, cf->log_rely_msg, logpath, &ss, "validate request dup err");
      zxid_set_fault(cf, ses, zxid_mk_fault(cf, 0, TAS3_PEP_RS_IN, "e:Client", "Duplicate Message.", "DuplicateMsg", 0, 0, 0));
      return 0;
    } else {
      INFO("Duplicate message detected, but configured to ignore this (DUP_MSG_FATAL=0). %d",0);
    }
  }
  zxlog_blob(cf, cf->log_rely_msg, logpath, &ss, "validate request");
  zxlogwsp(cf, ses, "K", "VALID", logpath->s, 0);
  return p;
}
