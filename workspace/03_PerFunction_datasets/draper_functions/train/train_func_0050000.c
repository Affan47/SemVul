CheckTimeout() {


  if ((read_state_ == STATE_READ_TIMEOUT) &&
      (write_state_ == STATE_WRITE_TIMEOUT)) {
    port_->thread()->Post(this, MSG_DELETE);
  }
}
