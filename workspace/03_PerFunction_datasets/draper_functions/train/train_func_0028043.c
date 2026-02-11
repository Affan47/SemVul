worker_thread_daemon(apr_thread_t * thread, void *selfv) {
  apr_status_t status;

  worker_t *worker = selfv;
  worker->mythread = thread;
  worker->flags |= FLAGS_CLIENT;

  worker->which = get_tot_threads(worker->global);
  inc_tot_threads(worker->global);
  worker->logger = logger_clone(worker->pbody, worker->logger, worker->which);

  worker_log(worker, LOG_INFO, "Daemon start ...");

  worker_log(worker, LOG_DEBUG, "unlock %s", worker->name);

  if ((status = worker->interpret(worker, worker, NULL)) != APR_SUCCESS) {
    goto error;
  }

  worker_flush(worker, worker->pbody);

  if ((status = worker_test_unused(worker)) != APR_SUCCESS) {
    goto error;
  }

  if ((status = worker_test_unused_errors(worker)) != APR_SUCCESS) {
    goto error;
  }

error:

  set_threads(worker->global, 1);
  worker_finally(worker, status);
  return NULL;
}
