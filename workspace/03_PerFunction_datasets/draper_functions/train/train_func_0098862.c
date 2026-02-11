zxid_wsc_prepare_call(zxid_conf* cf, zxid_ses* ses, zxid_epr* epr, const char* az_cred, const char* enve)
{
  struct zx_str* ret;
  struct zx_e_Envelope_s* env;

  if (!cf || !ses || !enve) {
    ERR("Missing mandatory arguments ses=%p (programmer error)", ses);
    return 0;
  }
  D_INDENT("prep: ");
  env = zxid_add_env_if_needed(cf, enve);
  if (!env) {
    D_DEDENT("prep: ");
    return 0;
  }


  if (!zxid_wsc_prep(cf, ses, epr, env)) {
    D_DEDENT("prep: ");
    return 0;
  }
  if (!zxid_wsc_prep_secmech(cf, ses, epr, env)) {
    D_DEDENT("prep: ");
    return 0;
  }
  ses->wsc_msgid = zx_str_to_c(cf->ctx, ZX_GET_CONTENT(env->Header->MessageID));


  if (!zxid_query_ctlpt_pdp(cf, ses, az_cred, env, TAS3_PEP_RQ_OUT,"e:Client", cf->pepmap_rqout)) {
    D_DEDENT("prep: ");
    return 0;
  }


  ret = zx_easy_enc_elem_opt(cf, &env->gg);
  D_DEDENT("prep: ");
  return ret;
}
