Get() {
  ScopedLock sl(lock_);
  CommandMessage result = queue_.Get();
  logger_->DebugEvent("Get", result.text());
  return result;
}
