lockExclusive(void) {
    lock_.lock();
    while(have_exclusive_lock() || have_shared_lock()) {
      cond_.wait(lock_);
    };
    ++exclusive_;
    thread_ = Glib::Thread::self();
    lock_.unlock();
  }
