extend(IDType& reservationID,
                                   Glib::TimeVal& expiryTime,
                                   Glib::TimeVal duration) {
    int amount;
    synchMutex.lock();
    amount = unsafeCancel(reservationID);
    if (amount > 0) {
      expiryTime = getExpiryTime(duration);
      reservationID = unsafeReserve(amount, expiryTime);
    }
    else {
      expiryTime = HISTORIC;
      reservationID = 0;
    }
    synchMutex.unlock();
    synchCond.signal();
  }
