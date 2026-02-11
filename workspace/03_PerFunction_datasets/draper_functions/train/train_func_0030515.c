zxid_eval_sol1(zxid_conf* cf, zxid_ses* ses, const char* obl, struct zxid_obl_list* req)
{
  char* oblig;
  struct zxid_obl_list* ol;
  struct zxid_obl_list* ob = 0;
  struct zxid_cstr_list* cs = 0;

  if (!obl) {
    if (!req)
      return 1;
    ERR("Fail: no pledges supplied and pledges required %p", req);
    return 0;
  }

  oblig = zx_dup_cstr(cf->ctx, obl);
  ol = zxid_load_obl_list(cf, 0, oblig);
  for (; req; req = req->n) {
    ob = zxid_find_obl_list(ol, req->name);
    if (!ob)
      goto fail;

    for (cs = ob->vals; cs; cs = cs->n)
      if (!zxid_find_cstr_list(req->vals, cs->s))
	goto fail;
  }

  INFO("OK: Pledges match requirements. Pledges(%s)", obl);
  zxid_free_obl_list(cf, ol);
  ZX_FREE(cf->ctx, oblig);
  return 1;

 fail:
  ERR("Fail: missing required obligation(%s), value(%s). Pledge(%s)", req?req->name:"-", cs?cs->s:"*", STRNULLCHKD(obl));
  zxid_free_obl_list(cf, ol);
  ZX_FREE(cf->ctx, oblig);
  return 0;
}
