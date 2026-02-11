zxid_show_protected_content_setcookie(zxid_conf* cf, zxid_cgi* cgi, zxid_ses* ses, int* res_len, int auto_flags)
{
  struct zx_str* issuer;
  struct zx_str* url;
  zxid_epr* epr;

  if (cf->ses_cookie_name && *cf->ses_cookie_name) {
    D("setcookie(%s)", cf->ses_cookie_name);
    ses->setcookie = zx_alloc_sprintf(cf->ctx, 0, "%s=%s; path=/%s",
				      cf->ses_cookie_name, ses->sid,
				      ONE_OF_2(cf->url[4], 's', 'S')?"; secure":"");
    ses->cookie = zx_alloc_sprintf(cf->ctx, 0, "$Version=1; %s=%s",
				   cf->ses_cookie_name, ses->sid);
  }
  if (cf->ptm_cookie_name && *cf->ptm_cookie_name) {
    D("ptm_cookie_name(%s)", cf->ptm_cookie_name);
    issuer = ZX_GET_CONTENT(ses->a7n->Issuer);
    if (!issuer)
      ERR("Assertion does not have Issuer. %p", ses->a7n->Issuer);

    if (epr = zxid_get_epr(cf, ses, TAS3_PTM, 0, 0, 0, 1)) {
      url = zxid_get_epr_address(cf, epr);
      if (!url)
	ERR("EPR does not have Address. %p", epr);
      ses->setptmcookie = zx_alloc_sprintf(cf->ctx, 0, "%s=%.*s?l0%.*s=1; path=/%s",
					   cf->ptm_cookie_name,
					   url?url->len:0, url?url->s:"",
					   issuer?issuer->len:0, issuer?issuer->s:"",
					   ONE_OF_2(cf->url[4], 's', 'S')?"; secure":"");

      D("setptmcookie(%s)", ses->setptmcookie);
    } else {
      D("The PTM epr could not be discovered. Has it been registered at discovery service? Is there a discovery service? %p", epr);
    }
  }
 erro:
  ses->rs = cgi->rs;
  return zxid_simple_ab_pep(cf, ses, res_len, auto_flags);
}
