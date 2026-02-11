OnEvent(uint32 ff, int err) {
    if ((ff & DE_READ) != 0) {
      enabled_events_ &= ~DE_READ;
      SignalReadEvent(this);
    }
    if ((ff & DE_WRITE) != 0) {
      enabled_events_ &= ~DE_WRITE;
      SignalWriteEvent(this);
    }
    if ((ff & DE_CONNECT) != 0) {
      enabled_events_ &= ~DE_CONNECT;
      SignalConnectEvent(this);
    }
    if ((ff & DE_ACCEPT) != 0) {
      enabled_events_ &= ~DE_ACCEPT;
      SignalReadEvent(this);
    }
    if ((ff & DE_CLOSE) != 0) {

      enabled_events_ = 0;
      SignalCloseEvent(this, err);
    }
  }
