ClientConfiguration_free(ClientConfiguration** cc)
{
  int i;
  assert(cc != NULL);
  if (cc == NULL) {
    return;
  }
  assert((*cc) != NULL);
  if ((*cc) == NULL) {
    return;
  }
  if ((*cc)->keysFile) {
    free((*cc)->keysFile);
    (*cc)->keysFile = NULL;
  }
  if ((*cc)->certificateFile) {
    free((*cc)->certificateFile);
    (*cc)->certificateFile = NULL;
  }
  if ((*cc)->storeFile) {
    free((*cc)->storeFile);
    (*cc)->storeFile = NULL;
  }
  if ((*cc)->realmsTable) {
    for (i = 0; i < (*cc)->realmsNumber; ++i) {
      if ((*cc)->realmsTable[i]) {
        ClientRealm_free(&((*cc)->realmsTable[i]));
      }
    }
    free((*cc)->realmsTable);
    (*cc)->realmsTable = NULL;
  }
  free((*cc));
  (*cc) = NULL;
}
