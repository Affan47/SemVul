initGlobals (void)
{
  globalLdap = (CPU_ldap *) malloc (sizeof (CPU_ldap));
  if (globalLdap == NULL)
    return -1;
  bzero (globalLdap, sizeof (CPU_ldap));
  globalLdap->make_home_directory = false;
  globalLdap->remove_home_directory = false;
  globalLdap->assume_yes = false;
  globalLdap->lock = false;
  globalLdap->unlock = false;
  globalLdap->port = -1;
  globalLdap->cn = NULL;
  globalLdap->exec = NULL;
  globalLdap->timeout.tv_sec = -10;
  globalLdap->version = 3;
  return 0;
}
