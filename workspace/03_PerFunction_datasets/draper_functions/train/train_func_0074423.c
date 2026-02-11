perf_serialize_clients(global_t *global, perf_host_t *host) {
  int i;
  apr_pool_t *ptmp;
  apr_table_entry_t *e;

  if (host->clients > 0) {
    apr_pool_create_unmanaged_ex(&ptmp, NULL, NULL);
    perf_serialize(host, "CLIENT %d\n", host->clients);
    e = (apr_table_entry_t *) apr_table_elts(host->worker->lines)->elts;
    for (i = 0; i < apr_table_elts(host->worker->lines)->nelts; ++i) {
      perf_serialize(host, "%s\n", e[i].val);
    }
    perf_serialize(host, "END\n");
    apr_pool_destroy(ptmp);
    host->clients = 0;
  }
  return APR_SUCCESS;
}
