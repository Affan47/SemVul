Close() {
    if (socket_) {
      return socket_->Close();
    }
    if (detect_) {
      detect_->Destroy(false);
      detect_ = NULL;
    }
    return 0;
  }
