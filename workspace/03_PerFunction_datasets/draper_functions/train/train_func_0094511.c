starttls_create_ctx (smtp_session_t session)
{
  SSL_CTX *ctx;
  char buf[2048];
  char buf2[2048];
  char *keyfile, *cafile, *capath;
  ckf_t status;


  ctx = SSL_CTX_new (TLSv1_client_method ());


  if (ctx_password_cb != NULL)
    {
      SSL_CTX_set_default_passwd_cb (ctx, ctx_password_cb);
      SSL_CTX_set_default_passwd_cb_userdata (ctx, ctx_password_cb_arg);
    }
  keyfile = user_pathname (buf, sizeof buf, "private/smtp-starttls.pem");
  status = check_file (keyfile);
  if (status == FILE_OK)
    {
      if (!SSL_CTX_use_certificate_file (ctx, keyfile, SSL_FILETYPE_PEM))
	{

	  return NULL;
	}
      if (!SSL_CTX_use_PrivateKey_file (ctx, keyfile, SSL_FILETYPE_PEM))
	{
	  int ok = 0;
	  if (session->event_cb != NULL)
	    (*session->event_cb) (session, SMTP_EV_NO_CLIENT_CERTIFICATE,
				  session->event_cb_arg, &ok);
	  if (!ok)
            return NULL;
	}
    }
  else if (status == FILE_PROBLEM)
    {
      if (session->event_cb != NULL)
	(*session->event_cb) (session, SMTP_EV_UNUSABLE_CLIENT_CERTIFICATE,
			      session->event_cb_arg, NULL);
      return NULL;
    }


  cafile = user_pathname (buf, sizeof buf, "ca.pem");
  status = check_file (cafile);
  if (status == FILE_NOT_PRESENT)
    cafile = NULL;
  else if (status == FILE_PROBLEM)
    {
      if (session->event_cb != NULL)
	(*session->event_cb) (session, SMTP_EV_UNUSABLE_CA_LIST,
			      session->event_cb_arg, NULL);
      return NULL;
    }
  capath = user_pathname (buf2, sizeof buf2, "ca");
  status = check_directory (capath);
  if (status == FILE_NOT_PRESENT)
    capath = NULL;
  else if (status == FILE_PROBLEM)
    {
      if (session->event_cb != NULL)
	(*session->event_cb) (session, SMTP_EV_UNUSABLE_CA_LIST,
			      session->event_cb_arg, NULL);
      return NULL;
    }


  if (cafile != NULL || capath != NULL)
    SSL_CTX_load_verify_locations (ctx, cafile, capath);
  else
    SSL_CTX_set_default_verify_paths (ctx);


  return ctx;
}
