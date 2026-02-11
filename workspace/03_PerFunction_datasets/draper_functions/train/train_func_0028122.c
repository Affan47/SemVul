WrapCurrentWithThreadManager(ThreadManager* thread_manager) {
  if (started_)
    return false;
#if defined(WIN32)


  thread_ = OpenThread(SYNCHRONIZE, FALSE, GetCurrentThreadId());
  if (!thread_) {
    LOG_GLE(LS_ERROR) << "Unable to get handle to thread.";
    return false;
  }
#elif defined(POSIX)
  thread_ = pthread_self();
#endif
  owned_ = false;
  started_ = true;
  thread_manager->SetCurrentThread(this);
  return true;
}
