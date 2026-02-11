block_SSL_LOAD_KEY(worker_t * worker, worker_t *parent, apr_pool_t *ptmp) {
  const char *val = store_get(worker->params, "1");
  char *copy = apr_pstrdup(worker->pbody, val);
  BIO *mem;

  ssl_wconf_t *config = ssl_get_worker_config(worker);

  if (config->pkey) {
    EVP_PKEY_free(config->pkey);
  }

  mem = BIO_new_mem_buf(copy, strlen(copy));
  config->pkey = PEM_read_bio_PrivateKey(mem,NULL,NULL,NULL);

  if (!config->pkey) {
    worker_log(worker, LOG_ERR, "Not a valid cert (PEM)");
    return APR_EINVAL;
  }
  return APR_SUCCESS;
}
