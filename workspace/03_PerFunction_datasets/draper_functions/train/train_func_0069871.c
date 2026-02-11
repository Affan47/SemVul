cvm_client_authenticate_password(const char* module,
			      const char* account,
			      const char* domain,
			      const char* password,
			      int split_account)
{
  struct cvm_credential creds[3];
  unsigned i;
  int result;
  memset(creds, 0, sizeof creds);
  result = doit(creds, module, account, domain, password, split_account);
  for (i = 0; i < 3; ++i)
    str_free(&creds[i].value);
  return result;
}
