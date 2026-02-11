calculateTimeout(timeval* howlong) const {
    static timeval timeout;

    if (!_queue->isEmpty()) {
	timeval curTime;

	curTime = TimerQueue::currentTime();
	if (_queue->earliestTime() > curTime) {
	    timeout = _queue->earliestTime() - curTime;
	    if (howlong == NULL || *howlong > timeout) {
		howlong = &timeout;
	    }
	} else {
	    timeout = TimerQueue::zeroTime();
	    howlong = &timeout;
	}
    }
    return howlong;
}
