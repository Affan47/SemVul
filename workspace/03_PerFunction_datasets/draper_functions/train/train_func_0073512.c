block_PERF_STAT(worker_t * worker, worker_t *parent,
                                    apr_pool_t *ptmp) {
  apr_status_t status;
  global_t *global = worker->global;
  perf_host_t *host = apr_pcalloc(global->pool, sizeof(*host));
  perf_gconf_t *gconf = perf_get_global_config(global);
  const char *param;

  if ((status = module_check_global(worker)) != APR_SUCCESS) {
    return status;
  }
  param = store_get(worker->params, "1");
  if (strcmp(param, "ON") == 0) {
    gconf->on = PERF_GCONF_ON;
  }
  else if (strcmp(param, "OFF") == 0) {
    gconf->on |= PERF_GCONF_OFF;
  }
  else if (strcmp(param, "LOG") == 0) {
    apr_status_t status;
    const char *filename;
    gconf->on |= PERF_GCONF_LOG;
    filename = store_get(worker->params, "2");
    if (filename) {
      if ((status = apr_file_open(&gconf->log_file, filename,
                                  APR_READ|APR_WRITE|APR_CREATE|APR_APPEND|APR_XTHREAD,
                                  APR_OS_DEFAULT, global->pool)) != APR_SUCCESS) {
        worker_log(worker, LOG_ERR, "Could not open log file \"%s\"", filename);
        return status;
      }
    }
    else {
      worker_log(worker, LOG_ERR, "No file specified for PERF:LOG command");
      return APR_EINVAL;
    }
  }

  return APR_SUCCESS;
}
