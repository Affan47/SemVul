Grow(size_t new_size) {
    if (size_ < new_size) {
      delete[] buf_;
      size_ = new_size;
      buf_ = new char[size_];
    }
  }
