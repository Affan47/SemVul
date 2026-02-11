set_text(std::auto_ptr<std::string>& text_) {
  Thread::Mutex::Lock lock(mutex);
  if (!ready) return false;
  text_a = text_;
  return true;
}
