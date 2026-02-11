zxid_add_env_if_needed(zxid_conf* cf, const char* enve)
{
  struct zx_e_Envelope_s* env;
  struct zx_root_s* r;
  r = zx_dec_zx_root(cf->ctx, strlen(enve), enve, "add_env");
  if (!r) {
    ERR("Malformed XML enve(%s)", enve);
    return 0;
  }
  env = r->Envelope;
  if (env) {
    DD("HERE1 ENV EXISTS %p", env);
    if (!env->Body)
      env->Body = zx_NEW_e_Body(cf->ctx, &env->gg);
    if (!env->Header)
      env->Header = zx_NEW_e_Header(cf->ctx, &env->gg);
  } else if (r->Body) {
    DD("HERE2 BODY EXISTS %p", env);
    env = zx_NEW_e_Envelope(cf->ctx,0);
    ZX_ADD_KID(env, Body, r->Body);
    if (r->Header)
      ZX_ADD_KID(env, Header, r->Header);
    else
      env->Header = zx_NEW_e_Header(cf->ctx, &env->gg);
  } else {
    ZX_FREE(cf->ctx, r);
    if (!memcmp(enve, "<?xml ", sizeof("<?xml ")-1)) {
      for (enve += sizeof("<?xml "); *enve && !(enve[0] == '?' && enve[1] == '>'); ++enve) ;
      if (*enve)
	enve += 2;
    }

    enve = zx_alloc_sprintf(cf->ctx, 0, "%s%s%s", zx_env_body_open, enve, zx_env_body_close);
    DD("HERE3 ADD ENV(%s)", enve);
    r = zx_dec_zx_root(cf->ctx, strlen(enve), enve, "add_env2");
    if (!r) {
      ERR("Malformed XML enve(%s)", enve);
      return 0;
    }
    env = r->Envelope;
  }
  ZX_FREE(cf->ctx, r);
  if (!env)
    ERR("No <e:Envelope> found in input argument. enve(%s)", enve);
  return env;
}
