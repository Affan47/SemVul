uv_timer_again(uv_timer_t* timer) {
  if (!ev_is_active(&timer->timer_watcher)) {
    uv_err_new((uv_handle_t*)timer, EINVAL);
    return -1;
  }

  ev_timer_again(EV_DEFAULT_UC_ &timer->timer_watcher);
  return 0;
}
