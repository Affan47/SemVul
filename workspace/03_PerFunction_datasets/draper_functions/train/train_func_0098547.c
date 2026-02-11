addDestination(LogDestination& destination) {
    Glib::Mutex::Lock lock(mutex);
    getContext().destinations.push_back(&destination);
  }
