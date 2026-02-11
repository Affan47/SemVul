releaseKeptMessages()
{
  keepingMessages_ = 0;
  while (!keptMessages_.empty()) {
    if (cancelled()) {
      allDone();
      return;
    }
    handler_->message(keptMessages_.get());
  }
}
