get_realmname(ServerConfiguration* config, int realm)
{
  static char realmname[10];

  assert(config != NULL);

  if (ServerRealm_get_realmName(ServerConfiguration_get_realmsTable(config)[realm]) == NULL) {
    memset(realmname, 0, 10);
    sprintf(realmname, "%d", realm);
    return realmname;
  }

  return ServerRealm_get_realmName(ServerConfiguration_get_realmsTable(config)[realm]);
}
