pull(int)
{
    if (_input < 0)
	return 0;
    else if (Packet *p = input(_input).pull()) {
	_notifier.set_active(true, false);
	return p;
    } else {
	if (!_signals[_input])
	    _notifier.set_active(false, false);
	return 0;
    }
}
