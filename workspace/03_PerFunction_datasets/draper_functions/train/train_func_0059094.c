VisitThread(ThreadLocalTop* top) {
    for (StackFrameIterator it(top); !it.done(); it.Advance()) {
      MarkCompactCollector::MarkObject(it.frame()->unchecked_code());
    }
  }
