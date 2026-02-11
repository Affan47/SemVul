listModule() {

  SECMODModuleList *mlp;
  SECMODModuleList *modules;
  SECMODListLock *moduleLock;

  modules = SECMOD_GetDefaultModuleList();
  moduleLock = SECMOD_GetDefaultModuleListLock();

  SECMOD_GetReadLock(moduleLock);

  fprintf(stdout, "<MODULES>\n");
  for(mlp = modules; mlp != NULL; mlp = mlp->next) {
    fprintf(stdout, "\t<%s></%s>\n",
            mlp->module->commonName,
            mlp->module->commonName);
  }
  fprintf(stdout, "</MODULES>\n");

  SECMOD_ReleaseReadLock(moduleLock);
}
