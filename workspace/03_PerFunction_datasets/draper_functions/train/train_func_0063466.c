SetDebugMessageDispatchHandler(
    v8::Debug::DebugMessageDispatchHandler handler, bool provide_locker) {
  ScopedLock with(dispatch_handler_access_);
  debug_message_dispatch_handler_ = handler;

  if (provide_locker && message_dispatch_helper_thread_ == NULL) {
    message_dispatch_helper_thread_ = new MessageDispatchHelperThread(isolate_);
    message_dispatch_helper_thread_->Start();
  }
}
