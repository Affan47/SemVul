worker_replace_vars(worker_t * worker, char *line, int *unresolved,
                           apr_pool_t *ptmp) {
  char *new_line;
  replacer_t *upcall_hook = apr_pcalloc(ptmp, sizeof(*upcall_hook));

  upcall_hook->worker = worker;
  upcall_hook->ptmp = ptmp;
  new_line = replacer(ptmp, line, upcall_hook, replacer_env_upcall);

  if (unresolved) {
    *unresolved = upcall_hook->unresolved;
  }
  return new_line;
}
