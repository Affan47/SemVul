StopReading() {
    if (!h || !*h)
      return DataStatus::NoLocationError;
    return (*h)->StopReading();
  }
