register_builtin_mechs (Gsasl * ctx)
{
  int rc = GSASL_OK;

#ifdef USE_ANONYMOUS
  rc = gsasl_register (ctx, &gsasl_anonymous_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_EXTERNAL
  rc = gsasl_register (ctx, &gsasl_external_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_LOGIN
  rc = gsasl_register (ctx, &gsasl_login_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_PLAIN
  rc = gsasl_register (ctx, &gsasl_plain_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_SECURID
  rc = gsasl_register (ctx, &gsasl_securid_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_NTLM
  rc = gsasl_register (ctx, &gsasl_ntlm_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_DIGEST_MD5
  rc = gsasl_register (ctx, &gsasl_digest_md5_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_CRAM_MD5
  rc = gsasl_register (ctx, &gsasl_cram_md5_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_SCRAM_SHA1
  rc = gsasl_register (ctx, &gsasl_scram_sha1_mechanism);
  if (rc != GSASL_OK)
    return rc;

  rc = gsasl_register (ctx, &gsasl_scram_sha1_plus_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_SAML20
  rc = gsasl_register (ctx, &gsasl_saml20_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_OPENID20
  rc = gsasl_register (ctx, &gsasl_openid20_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_GSSAPI
  rc = gsasl_register (ctx, &gsasl_gssapi_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

#ifdef USE_GS2
  rc = gsasl_register (ctx, &gsasl_gs2_krb5_mechanism);
  if (rc != GSASL_OK)
    return rc;
#endif

  return GSASL_OK;
}
