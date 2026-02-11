removeTimer(Timer &T) {
  sys::SmartScopedLock<true> L(*TimerLock);


  if (T.Started)
    TimersToPrint.push_back(std::make_pair(T.Time, T.Name));

  T.TG = nullptr;


  *T.Prev = T.Next;
  if (T.Next)
    T.Next->Prev = T.Prev;


  if (FirstTimer || TimersToPrint.empty())
    return;

  raw_ostream *OutStream = CreateInfoOutputFile();
  PrintQueuedTimers(*OutStream);
  delete OutStream;
}
