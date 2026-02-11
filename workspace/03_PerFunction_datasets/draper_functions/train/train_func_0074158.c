status() const {
    if (status_.ok()) {
      return iter_->status();
    } else {
      return status_;
    }
  }
