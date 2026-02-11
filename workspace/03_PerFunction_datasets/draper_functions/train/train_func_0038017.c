Destroy() {
  LOG_J(LS_VERBOSE, this) << "Connection destroyed";
  set_read_state(STATE_READ_TIMEOUT);
  set_write_state(STATE_WRITE_TIMEOUT);
}
