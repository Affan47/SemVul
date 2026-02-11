StartGCTimer () {
  if (!ev_is_active(&gc_timer)) {
    ev_timer_start(EV_DEFAULT_UC_ &gc_timer);
    ev_unref(EV_DEFAULT_UC);
  }
}
