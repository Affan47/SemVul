ProcessHeaderComplete(bool chunked, size_t& data_size,
                                HttpError* error) {
  StreamInterface* old_docstream = doc_stream_;
  if (notify_) {
    *error = notify_->onHttpHeaderComplete(chunked, data_size);

    ASSERT(NULL != data_);
  }
  if ((HE_NONE == *error) && (NULL != data_->document.get())) {
    data_->document->SignalEvent.connect(this, &HttpBase::OnDocumentEvent);
  }
  if (HE_NONE != *error) {
    return PR_COMPLETE;
  }
  if (old_docstream != doc_stream_) {

    return PR_BLOCK;
  }
  return PR_CONTINUE;
}
