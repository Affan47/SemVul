cgu_tracked_callback_wrapper(void* data) {
  const Cgu::SafeEmitter* e = static_cast<Cgu::SafeEmitter*>(data);


  Cgu::Thread::CancelBlock b;
  try {
    e->emit();
  }
  catch (...) {
    g_critical("Exception thrown in tracked_callback_wrapper() for Callback::post() function\n");
  }
  delete e;
  return false;
}
