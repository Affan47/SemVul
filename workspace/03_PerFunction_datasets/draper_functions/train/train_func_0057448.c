setPrivateKeyPasswd(const char *thePasswd)
{
  if (thePasswd) privateKeyPasswd = thePasswd;
  else privateKeyPasswd.clear();

  if (transportLayerContext)
  {

    SSL_CTX_set_default_passwd_cb(transportLayerContext, DcmTLSTransportLayer_passwordCallback);
    SSL_CTX_set_default_passwd_cb_userdata(transportLayerContext, &privateKeyPasswd);
  }
  return;
}
