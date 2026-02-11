reserve(int amount,
                                             Glib::TimeVal duration,
                                             bool prioritized,
                                             Glib::TimeVal timeOut) {
    Glib::TimeVal deadline = getExpiryTime(timeOut);
    Glib::TimeVal expiryTime;
    IDType reservationID;
    synchMutex.lock();
    while (amount > unsafeGetValue() + (prioritized ? excess : 0) and
           getCurrentTime() < deadline)
      synchCond.timed_wait(synchMutex,
                           std::min(deadline, unsafeGetNextExpiration()));
    if (amount <= unsafeGetValue() + (prioritized ? excess : 0)) {
      expiryTime = getExpiryTime(duration);
      reservationID = unsafeReserve(amount, expiryTime);
    }
    else {
      expiryTime = HISTORIC;
      reservationID = 0;
    }
    synchMutex.unlock();
    return getCounterTicket(reservationID, expiryTime, this);
  }
