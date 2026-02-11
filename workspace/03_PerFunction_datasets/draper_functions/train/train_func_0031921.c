StopWorker() {
    busy_worker_->set_stop_work(true);
    busy_worker_->Join();
    delete busy_worker_;
  }
