initialize(ErrorHandler *)
{
  _timer.initialize(this);
  if (_active)
    _timer.schedule_after_msec(_interval);
  return 0;
}
