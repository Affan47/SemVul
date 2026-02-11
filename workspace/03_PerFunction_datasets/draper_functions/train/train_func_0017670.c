Csec_server_get_client_fqans(Csec_context_t *ctx, int *nbfqan) {
  SAVE_ERR;
  Csec_clear_errmsg();
  if (ctx == NULL) {
    serrno = EINVAL;
    return NULL;
  }
  if (nbfqan != NULL) {
    *nbfqan = ctx->nbfqan;
  }
  RESTORE_ERR(0);
  return ctx->fqan;
}
