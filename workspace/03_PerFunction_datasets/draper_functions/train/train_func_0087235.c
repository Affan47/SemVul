do_status_line(self_t *self, worker_t *worker,
                                   apr_pool_t *p, char *status_line,
				   int write) {
  apr_status_t status;

  if ((status = call_command(worker, command_DATA, "__", status_line))
      != APR_SUCCESS) {
    return status;
  }

  if (write) {
    apr_file_printf(self->ofp, "\n_EXPECT . \"%s\"", status_line);
  }

  return status;
}
