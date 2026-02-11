IsInitialized() const {

  if (has_options()) {
    if (!this->options().IsInitialized()) return false;
  }
  return true;
}
