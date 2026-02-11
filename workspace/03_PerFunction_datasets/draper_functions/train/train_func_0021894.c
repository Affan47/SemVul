Start()
  {
    if(_running) {
      return;
    }

    listen(_host, _port);
    _running = true;
  }
