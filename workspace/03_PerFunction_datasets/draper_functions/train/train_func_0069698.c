EnableSlidingStateWindow() {
#ifdef ENABLE_LOGGING_AND_PROFILING


  if (ticker_ == NULL) {
    FLAG_sliding_state_window = true;
    return;
  }


  if (sliding_state_window_ == NULL) {
    sliding_state_window_ = new SlidingStateWindow();
  }
#endif
}
