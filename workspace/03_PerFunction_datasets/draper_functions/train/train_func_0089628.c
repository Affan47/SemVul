start(std::size_t interval)
{
    if( _active)
        stop();

    _active = true;
    _interval = interval;
    _remaining = int64_t(_interval) * 1000;
    _finished = Clock::getSystemTicks() + _remaining;

    if(_selector)
        _selector->onTimerChanged(*this);
}
