unsafeCancel(IDType reservationID) {
    std::map<IDType, int>::iterator resIter = reservations.find(reservationID);
    int amount = 0;
    if (resIter != reservations.end()) {
      amount = resIter->second;
      value += amount;
      reservations.erase(resIter);
    }
    return amount;
  }
