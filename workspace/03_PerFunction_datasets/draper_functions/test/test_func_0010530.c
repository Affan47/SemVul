uv_ares_init_options(uv_loop_t* loop, ares_channel *channelptr,
    struct ares_options *options, int optmask) {
  int rc;


  if (loop->channel != NULL) {
    uv_err_new_artificial(loop, UV_EALREADY);
    return -1;
  }


  options->sock_state_cb = uv__ares_sockstate_cb;
  options->sock_state_cb_data = loop;
  optmask |= ARES_OPT_SOCK_STATE_CB;


  rc = ares_init_options(channelptr, options, optmask);


  if (rc == ARES_SUCCESS) {
    loop->channel = *channelptr;
  }


  ev_init(&loop->timer, uv__ares_timeout);
  loop->timer.repeat = 1.0;

  return rc;
}
