HandleAllTimedOut() {


  if (!was_timed_out_) {


    Allocate();
  }


  was_timed_out_ = true;
  was_writable_ = false;
  set_writable(false);
}
