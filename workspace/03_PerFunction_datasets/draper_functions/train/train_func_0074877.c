command_BPS(command_t *self, worker_t *worker, char *data,
                         apr_pool_t *ptmp) {
  apr_status_t status;
  worker_t *body;
  char *copy;
  int bps;
  int duration;
  char **argv;
  apr_time_t init;
  apr_time_t start;
  apr_time_t cur;

  COMMAND_NEED_ARG("Byte/s and duration time in second");

  my_tokenize_to_argv(copy, &argv, ptmp, 0);
  bps = apr_atoi64(argv[0]);
  duration = apr_atoi64(argv[1]);


  if ((status = worker_body(&body, worker)) != APR_SUCCESS) {
    return status;
  }


  init = apr_time_now();
  for (;;) {

    start = apr_time_now();
    if ((status = body->interpret(body, worker, NULL)) != APR_SUCCESS) {
      break;
    }
    cur = apr_time_now();

    if (bps > 0) {

      while ((cur - start == 0)) {

        apr_sleep(1000);
        cur = apr_time_now();
      }


      while (((body->sent * APR_USEC_PER_SEC) / (cur - start)) > bps ) {

        apr_sleep(1000);
        cur = apr_time_now();
      }
    }


    body->sent = 0;


    if (apr_time_sec(cur - init) >= duration) {
      goto end;
    }
  }

end:
  worker_log(worker, LOG_CMD, "_END");

  worker_body_end(body, worker);

  return status;
}
