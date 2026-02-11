QueueCallback(TimerCallback *callback, int due_time)
  {
    TimerEvent te(callback, due_time);
    QueueEvent(te);
    return te;
  }
