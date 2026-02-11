soap_wsse_add_BinarySecurityTokenPEM(struct soap *soap, const char *id, const char *filename)
{ FILE *fd;
  DBGFUN2("soap_wsse_add_BinarySecurityTokenPEM", "id=%s", id?id:"", "filename=%s", filename?filename:"");
  if ((fd = fopen(filename, "r")))
  {
    X509 *cert = PEM_read_X509(fd, NULL, NULL, NULL);
    fclose(fd);

    if (cert)
    { int err = soap_wsse_add_BinarySecurityTokenX509(soap, id, cert);
      X509_free(cert);
      return err;
    }
  }
  return soap_wsse_fault(soap, wsse__InvalidSecurityToken, "Missing certificate");
}
