Terminate() {
  ASSERT(initialized_);
  if (!initialized_) {
    return;
  }
  Send(MSG_TERMINATE, NULL);
  media_engine_->Terminate();
  initialized_ = false;
}
