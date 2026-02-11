zxid_sp_dig_sso_a7n(zxid_conf* cf, zxid_cgi* cgi, zxid_ses* ses, struct zx_sp_Response_s* resp)
{
  zxid_a7n* a7n;
  struct zx_ns_s* pop_seen = 0;

  if (!zxid_chk_sig(cf, cgi, ses, &resp->gg, resp->Signature, resp->Issuer, 0, "Response"))
    return 0;

  a7n = zxid_dec_a7n(cf, resp->Assertion, resp->EncryptedAssertion);
  if (a7n) {
    zx_see_elem_ns(cf->ctx, &pop_seen, &resp->gg);
    return zxid_sp_sso_finalize(cf, cgi, ses, a7n, pop_seen);
  }
  if (cf->anon_ok && cgi->rs && !strcmp(cf->anon_ok, cgi->rs))
    return zxid_sp_anon_finalize(cf, cgi, ses);
  ERR("No Assertion found and not anon_ok in SAML Response %d", 0);
  zxlog(cf, 0, 0, 0, 0, 0, 0, ZX_GET_CONTENT(ses->nameid), "N", "C", "ERR", 0, "sid(%s) No assertion", ses->sid?ses->sid:"");
  return 0;
}
