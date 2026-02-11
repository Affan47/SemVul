close_all() {
  while (true) {
    if (!get_active()) {
      return true;
    }
    if (!close()) {
      return false;
    }
  }
}
