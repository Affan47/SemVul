unsafeGetValue() {
    while (unsafeGetNextExpiration() < getCurrentTime()) {
      unsafeCancel(selfExpiringReservations.top().getReservationID());
      selfExpiringReservations.pop();
    }
    return value;
  }
