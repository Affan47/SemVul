config_destroy (stud_config *cfg) {

  if (cfg == NULL) return;


  if (cfg->CHROOT != NULL) free(cfg->CHROOT);
  if (cfg->FRONT_IP != NULL) free(cfg->FRONT_IP);
  if (cfg->FRONT_PORT != NULL) free(cfg->FRONT_PORT);
  if (cfg->BACK_IP != NULL) free(cfg->BACK_IP);
  if (cfg->BACK_PORT != NULL) free(cfg->BACK_PORT);
  if (cfg->CERT_FILES != NULL) {
    struct cert_files *curr = cfg->CERT_FILES, *next;
    while (cfg->CERT_FILES != NULL) {
      next = curr->NEXT;
      free(curr);
      curr = next;
    }
  }
  if (cfg->CIPHER_SUITE != NULL) free(cfg->CIPHER_SUITE);
  if (cfg->ENGINE != NULL) free(cfg->ENGINE);

#ifdef USE_SHARED_CACHE
  if (cfg->SHCUPD_IP != NULL) free(cfg->SHCUPD_IP);
  if (cfg->SHCUPD_PORT != NULL) free(cfg->SHCUPD_PORT);

  for (int i = 0; i < MAX_SHCUPD_PEERS; i++) {
    if (cfg->SHCUPD_PEERS[i].ip != NULL)
      free(cfg->SHCUPD_PEERS[i].ip);
    if (cfg->SHCUPD_PEERS[i].port != NULL)
      free(cfg->SHCUPD_PEERS[i].port);
  }

  if (cfg->SHCUPD_MCASTIF != NULL) free(cfg->SHCUPD_MCASTIF);
  if (cfg->SHCUPD_MCASTTTL != NULL) free(cfg->SHCUPD_MCASTTTL);
#endif

  free(cfg);
}
