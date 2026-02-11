cvm_module_lookup(void)
{
  int err;
  if ((err = cvm_getpwnam(cvm_module_credentials[CVM_CRED_ACCOUNT].s, &pw)) != 0)
    return err;
  if (pw->pw_passwd == 0) return CVME_PERMFAIL;
  return 0;
}
