onHttpComplete(HttpMode mode, HttpError err) {
  if (mode == HM_SEND) {
    ASSERT(current_ != NULL);
    signalling_ = true;
    server_->SignalHttpRequestComplete(server_, current_, err);
    signalling_ = false;
    if (close_) {

      err = HE_DISCONNECTED;
    }
  }
  if (err != HE_NONE) {
    server_->Remove(connection_id_);
  } else if (mode == HM_CONNECT) {
    base_.recv(&current_->request);
  } else if (mode == HM_RECV) {
    ASSERT(current_ != NULL);


    HttpServerTransaction* transaction = current_;
    current_ = NULL;
    server_->SignalHttpRequest(server_, transaction);
  } else if (mode == HM_SEND) {
    Thread::Current()->Dispose(current_->response.document.release());
    current_->request.clear(true);
    current_->response.clear(true);
    base_.recv(&current_->request);
  } else {
    ASSERT(false);
  }
}
