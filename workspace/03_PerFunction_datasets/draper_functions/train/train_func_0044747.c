send(HttpData* data) {
  ASSERT(HM_NONE == mode_);
  if (mode_ != HM_NONE) {
    return;
  } else if (!isConnected()) {
    OnHttpStreamEvent(http_stream_, SE_CLOSE, HE_DISCONNECTED);
    return;
  }

  mode_ = HM_SEND;
  data_ = data;
  len_ = 0;
  ignore_data_ = chunk_data_ = false;

  if (data_->document.get()) {
    data_->document->SignalEvent.connect(this, &HttpBase::OnDocumentEvent);
  }

  std::string encoding;
  if (data_->hasHeader(HH_TRANSFER_ENCODING, &encoding)
      && (encoding == "chunked")) {
    chunk_data_ = true;
  }

  len_ = data_->formatLeader(buffer_, sizeof(buffer_));
  len_ += strcpyn(buffer_ + len_, sizeof(buffer_) - len_, "\r\n");

  header_ = data_->begin();
  if (header_ == data_->end()) {

    queue_headers();
  }

  flush_data();
}
