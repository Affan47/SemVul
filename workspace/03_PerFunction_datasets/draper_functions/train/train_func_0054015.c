update() {
  Timestamp now;
  bool u = false;
  if (host) {
    switch(active) {
    case CLK_WHITE_RUNNING:
      now=Timestamp::now();
      value[0]=val_ref[0]+(countdownf?-1:1)*(int)((now-t_ref[0])*1000.0);
      u = true;
      break;
    case CLK_BLACK_RUNNING:
      now=Timestamp::now();
      value[1]=val_ref[1]+(countdownf?-1:1)*(int)((now-t_ref[1])*1000.0);
      u = true;
      break;
    }
    if (u) {
      host->updateClock();
      if (host2) host2->updateClock();
    }
  }
}
