QueueEvent(TimerEvent te)
  {
    _queue.push(te);
    if(_queue.top() == te && _real_time) {
      if(_next_timer != -1) {
        killTimer(_next_timer);
      }
      _next_timer = startTimer(0);
    }
  }
