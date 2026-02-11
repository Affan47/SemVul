calculateSpeed()
{
  int64_t now = global::wallclock().getTimeInMillis();
  removeStaleTimeSlot(now);
  if(timeSlots_.empty()) {
    return 0;
  }
  int64_t elapsed = now - timeSlots_[0].first;
  if(elapsed <= 0) {
    elapsed = 1;
  }
  int speed = bytesWindow_*1000/elapsed;
  maxSpeed_ = std::max(speed, maxSpeed_);
  return speed;
}
