zxid_mk_an_stmt(zxid_conf* cf, zxid_ses* ses, struct zx_elem_s* father, const char* eid)
{
  struct zx_str sesix;
  struct zx_str eid_ss;
  struct zx_str* ss;
  struct zx_sa_AuthnStatement_s* an_stmt = zx_NEW_sa_AuthnStatement(cf->ctx, father);
  if (ses->sesix) {
#if 0
    an_stmt->SessionIndex = zx_dup_str(cf->ctx, ses->sesix);
#else

    eid_ss.len = strlen(eid);
    eid_ss.s = (char*)eid;
    sesix.len = strlen(ses->sesix);
    sesix.s = ses->sesix;
    ss = zxid_psobj_enc(cf, &eid_ss, "ZS", &sesix);
    an_stmt->SessionIndex = zx_ref_len_attr(cf->ctx, &an_stmt->gg, zx_SessionIndex_ATTR, ss->len, ss->s);
#endif
  }
  an_stmt->AuthnInstant = zxid_date_time_attr(cf, &an_stmt->gg, zx_AuthnInstant_ATTR, ses->an_instant);
  an_stmt->AuthnContext = zx_NEW_sa_AuthnContext(cf->ctx, &an_stmt->gg);
  if (ses->an_ctx)
    an_stmt->AuthnContext->AuthnContextClassRef
      = zx_dup_elem(cf->ctx, &an_stmt->AuthnContext->gg, zx_sa_AuthnContextClassRef_ELEM, ses->an_ctx);
  else {
    ERR("Session(%s) lacks AuthentContextClassRef. Output AuthnStatement will not satisfy all processing rules. See configuration option ISSUE_AUTHNCTX_PW.", ses->sesix);
  }
  return an_stmt;
}
