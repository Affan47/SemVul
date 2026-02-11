removeDestinations(void) {
    Glib::Mutex::Lock lock(mutex);
    getContext().destinations.clear();
  }
