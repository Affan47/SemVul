Start() {
  if (!counter_.Enabled())
    return;
  stop_time_ = 0;
  start_time_ = OS::Ticks();
}
