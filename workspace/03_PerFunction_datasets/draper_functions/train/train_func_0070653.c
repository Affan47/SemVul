block_GET_TRANSPORT_OBJECT(worker_t *worker, worker_t *parent, apr_pool_t *ptmp) {
  apr_status_t status = APR_SUCCESS;
  const char *name;
  const char *sym;
  const char *config;
  transport_t *transport;
  apr_dso_handle_t *dso;
  apr_dso_handle_sym_t dso_sym;
  transport_dso_t *transport_dso;
  global_t *global = worker->global;
  dso_gconf_t *gconf = dso_get_global_config(global);

  name = store_get(worker->params, "1");
  if (!name) {
    worker_log(worker, LOG_ERR, "Expect name loaded share library");
    return APR_EINVAL;
  }

  if ((dso = apr_hash_get(gconf->transport_objs, name, APR_HASH_KEY_STRING)) == NULL) {
    worker_log(worker, LOG_ERR, "Requested share library not found");
    return APR_EINVAL;
  }

  sym = store_get(worker->params, "2");
  if (!sym) {
    worker_log(worker, LOG_ERR, "Expect a unique name for this object");
    return APR_EINVAL;
  }

  if ((status = apr_dso_sym(&dso_sym, dso, sym)) != APR_SUCCESS) {
    worker_log(worker, LOG_ERR, "Can not load \"%s\" object", sym);
    return status;
  }

  transport_dso = (transport_dso_t *)dso_sym;

  config = store_get(worker->params, "3");
  if (config) {
    if ((status = transport_dso->configure(transport_dso->custom_handle(),
                                           config)) != APR_SUCCESS) {
      worker_log(worker, LOG_ERR, "Configure failed, see logs of your dso module");
      return status;
    }
  }


  transport = transport_new(transport_dso, worker->pbody,
			    dso_transport_os_desc_get,
			    dso_transport_set_timeout,
			    dso_transport_get_timeout,
			    dso_transport_read,
			    dso_transport_write);

  worker_get_socket(worker, name, apr_pstrcat(global->pool, "000:", sym, NULL));
  transport_register(worker->socket, transport);

  return status;
}
