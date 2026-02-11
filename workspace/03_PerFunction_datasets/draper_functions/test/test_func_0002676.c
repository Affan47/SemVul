ServerRealm_increase_connectedClients(ServerRealm* sr)
{
  assert(sr != NULL);
  if (sr == NULL) {
    return;
  }
  ServerRealm_set_connectedClients(sr, ServerRealm_get_connectedClients(sr) + 1);
}
