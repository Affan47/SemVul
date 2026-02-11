cancel()
{
    if (!_fired) TimedEventService::instance()->unregisterEvent(this);
    _fired = true;
}
