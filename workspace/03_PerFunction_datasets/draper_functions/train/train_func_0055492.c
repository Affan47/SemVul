StopThread() {
    keep_running_ = false;
    wait_for_ever_semaphore_->Signal();


    Join();

    if (data_ready_semaphore_ != NULL) {
      delete data_ready_semaphore_;
      data_ready_semaphore_ = NULL;
    }

    delete wait_for_ever_semaphore_;
    wait_for_ever_semaphore_ = NULL;
  }
