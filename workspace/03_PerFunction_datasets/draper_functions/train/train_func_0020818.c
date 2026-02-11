command_RECORD(command_t *self, worker_t *worker, char *data,
                            apr_pool_t *ptmp) {
  char *copy;
  recorder_t *recorder = worker_get_recorder(worker);
  COMMAND_NEED_ARG("RES [ALL] {STATUS|HEADERS|BODY}*");

  if (strncmp(copy, "RES", 3) != 0) {
    worker_log(worker, LOG_ERR, "Only response recording supported yet");
    return APR_EINVAL;
  }

  if (strstr(copy, "ALL")) {
    recorder->flags = RECORDER_RECORD_ALL;
  }
  if (strstr(copy, "STATUS")) {
    recorder->flags |= RECORDER_RECORD_STATUS;
  }
  if (strstr(copy, "HEADERS")) {
    recorder->flags |= RECORDER_RECORD_HEADERS;
  }
  if (strstr(copy, "BODY")) {
    recorder->flags |= RECORDER_RECORD_BODY;
  }

  if (recorder->on) {

    sockreader_destroy(&recorder->sockreader);
  }


  sockreader_new(&recorder->sockreader, NULL, NULL, 0);

  recorder->on = RECORDER_RECORD;

  return APR_SUCCESS;
}
