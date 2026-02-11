Start() {
  if (GetHistogram() != NULL) {
    stop_time_ = 0;
    start_time_ = OS::Ticks();
  }
}
