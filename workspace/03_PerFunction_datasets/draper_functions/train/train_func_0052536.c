qos_cleanup_inctx(void *p) {
  qos_ifctx_t *inctx = p;
  qos_srv_config *sconf = inctx->sconf;
#if APR_HAS_THREADS
  if(sconf->inctx_t && !sconf->inctx_t->exit) {
    apr_thread_mutex_lock(sconf->inctx_t->lock);
    inctx->status = QS_CONN_STATE_DESTROY;
    apr_table_unset(sconf->inctx_t->table,
                    QS_INCTX_ID);
    apr_thread_mutex_unlock(sconf->inctx_t->lock);
  }
#endif
  return APR_SUCCESS;
}
