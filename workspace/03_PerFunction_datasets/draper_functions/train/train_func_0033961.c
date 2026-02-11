cgu_timeout_wrapper(void* data) {
  const Cgu::Callback::CallbackArg<bool&>* cb = static_cast<Cgu::Callback::CallbackArg<bool&>*>(data);

  bool keep_source = true;


  Cgu::Thread::CancelBlock b;
  try {
    cb->dispatch(keep_source);
  }
  catch (...) {
    g_critical("Exception thrown in timeout_wrapper() for timeout function\n");
  }
  return keep_source;
}
