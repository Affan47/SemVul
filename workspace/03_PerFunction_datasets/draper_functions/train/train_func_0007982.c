OnEvent(uint32 ff, int err) {
    if ((ff & DE_READ) != 0)
      SignalReadEvent(this);
    if ((ff & DE_WRITE) != 0)
      SignalWriteEvent(this);
    if ((ff & DE_CLOSE) != 0)
      SignalCloseEvent(this, err);
  }
