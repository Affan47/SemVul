imclient_starttls(struct imclient *imclient,
			     char *cert_file,
			     char *key_file,
                             char *CAfile,
                             char *CApath)
{
#ifdef HAVE_SSL
  int result;
  struct authresult theresult;
  sasl_ssf_t ssf;
  char *auth_id;

  imclient_send(imclient, tlsresult, (void *)&theresult,
		"STARTTLS");


  imclient->readytag = imclient->gensym;
  while (imclient->readytag) {
    imclient_processoneevent(imclient);
  }

  result=tls_init_clientengine(imclient, 10, cert_file, key_file,
                               CAfile, CApath);
  if (result!=0)
  {
    printf("[ TLS engine failed ]\n");
    return 1;
  } else {
    result=tls_start_clienttls(imclient, &ssf, &auth_id, imclient->fd);

    if (result!=0) {
      printf("[ TLS negotiation did not succeed ]\n");
      return 1;
    }
  }


  imclient->tls_on = 1;

  auth_id="";


  result=sasl_setprop(imclient->saslconn,
		      SASL_SSF_EXTERNAL,
		      &ssf);
  if (result!=SASL_OK) return 1;
  result=sasl_setprop(imclient->saslconn,
		      SASL_AUTH_EXTERNAL,
		      auth_id);
  if (result!=SASL_OK) return 1;

  return 0;
#else
  printf("[ TLS support not present (imclient_starttls) ]\n");
  return 1;
#endif
}
