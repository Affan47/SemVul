StopWork() {
  if (!worker_thread_) {

    return true;
  } else if (worker_thread_ != talk_base::Thread::Current()) {
    LOG(LS_ERROR) << "Stopping from a different thread is not supported";
    ASSERT(false);
    return false;
  }
  OnStop();
  worker_thread_->Clear(this, MSG_HAVEWORK);
  worker_thread_ = NULL;
  return true;
}
