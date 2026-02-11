command_RESWAIT(command_t * self, worker_t * worker, char * data,
                             apr_pool_t *ptmp) {
  apr_status_t status;
  do {
    status = command_RES(self, worker, "", ptmp);
    if(status != APR_SUCCESS) {
      return status;
    }
    status = command_WAIT(self, worker, "", ptmp);
    if(status == APR_EOF) {

      command_CLOSE(self, worker, "do not test expects", ptmp);
    }
  } while(status == APR_EOF);
  return status;
}
