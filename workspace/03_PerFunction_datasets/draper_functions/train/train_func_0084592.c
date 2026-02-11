TransferLocations() const {
    if (!h || !*h) {
      std::vector<URL> empty_vector;
      return empty_vector;
    }
    return (*h)->TransferLocations();
  }
