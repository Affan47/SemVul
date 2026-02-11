TearDown() {
#ifdef ENABLE_LOGGING_AND_PROFILING
  LogMessageBuilder::set_write_failure_handler(NULL);


  if (profiler_ != NULL) {
    profiler_->Disengage();
    delete profiler_;
    profiler_ = NULL;
  }

  delete compression_helper_;
  compression_helper_ = NULL;

  delete sliding_state_window_;
  sliding_state_window_ = NULL;

  delete ticker_;
  ticker_ = NULL;

  Log::Close();
#endif
}
