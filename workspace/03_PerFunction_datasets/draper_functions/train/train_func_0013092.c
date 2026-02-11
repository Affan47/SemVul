initialize(ErrorHandler *)
{
    _timer.initialize(this);
    _upstream_signal = Notifier::upstream_empty_signal(this, 0, 0, &_notifier);
    return 0;
}
