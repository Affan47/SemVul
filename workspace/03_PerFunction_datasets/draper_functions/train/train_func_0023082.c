qos_rctx_config_get(request_rec *r) {
  qs_req_ctx *rctx = ap_get_module_config(r->request_config, &qos_module);
  if(rctx == NULL) {
    rctx = apr_pcalloc(r->pool, sizeof(qs_req_ctx));
    rctx->entry = NULL;
    rctx->entry_cond = NULL;
    rctx->evmsg = NULL;
    rctx->is_vip = 0;
    rctx->event_entries = apr_table_make(r->pool, 1);
    rctx->maxpostcount = 0;
    rctx->event_kbytes_per_sec_block_rate = 0;
    rctx->cc_event_req_set = 0;
    rctx->cc_serialize_set = 0;
    rctx->body_window = NULL;
    ap_set_module_config(r->request_config, &qos_module, rctx);
  }
  return rctx;
}
