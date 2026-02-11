ClientRealm_free(ClientRealm** cr)
{
  assert(cr != NULL);
  if (cr == NULL) {
    return;
  }
  assert((*cr) != NULL);
  if ((*cr) == NULL) {
    return;
  }
  ClientRealm_set_serverName((*cr), NULL);
  ClientRealm_set_managePort((*cr), NULL);
  ClientRealm_set_hostName((*cr), NULL);
  ClientRealm_set_realmName((*cr), NULL);
  ClientRealm_set_sKeepAliveTimeout((*cr), NULL);
  ClientRealm_set_realmId((*cr), NULL);
  ClientRealm_set_localName((*cr), NULL);
  ClientRealm_set_localPort((*cr), NULL);
  ClientRealm_set_localDestinationName((*cr), NULL);
  ClientRealm_set_clientAddress((*cr), NULL);
  ClientRealm_set_masterSslFd((*cr), NULL);
  ClientRealm_set_httpProxyOptions((*cr), NULL);
  ClientRealm_set_arOptions((*cr), NULL);
  ClientRealm_set_destinationPorts((*cr), NULL);
  ClientRealm_set_usersTable((*cr), NULL);
#ifdef HAVE_LIBDL
  ClientRealm_set_userModule((*cr), NULL);
  ClientRealm_set_serviceModule((*cr), NULL);
#endif
  free((*cr));
  (*cr) = NULL;
}
