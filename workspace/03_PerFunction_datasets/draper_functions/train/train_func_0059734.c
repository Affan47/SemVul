Stop() {
  if (file_read_thread_) {
    file_read_thread_->Stop();
    file_read_thread_ = NULL;
    LOG(LS_INFO) << "File video capturer '" << GetId() << "' stopped";
  }
  SetCaptureFormat(NULL);
}
