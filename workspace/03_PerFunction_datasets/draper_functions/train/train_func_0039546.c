EnableHandler() {
  RAW_CHECK(prof_handler_token_ == NULL, "SIGPROF handler already registered");
  prof_handler_token_ = ProfileHandlerRegisterCallback(prof_handler, this);
  RAW_CHECK(prof_handler_token_ != NULL, "Failed to set up SIGPROF handler");
}
