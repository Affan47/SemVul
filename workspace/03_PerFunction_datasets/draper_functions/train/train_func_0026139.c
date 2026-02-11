uv_timer_stop(uv_timer_t* timer) {
  if (ev_is_active(&timer->timer_watcher)) {
    ev_ref(EV_DEFAULT_UC);
  }

  ev_timer_stop(EV_DEFAULT_UC_ &timer->timer_watcher);
  return 0;
}
