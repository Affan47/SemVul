Next(MCCInterface *next, const std::string& label) {
    Glib::Mutex::Lock lock(next_lock_);
    if (next == NULL) next_.erase(label);
    else next_[label] = next;
  }
