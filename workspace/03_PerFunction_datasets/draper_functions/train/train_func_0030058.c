print_to_file(const char* filename) {

  {
    Thread::Mutex::Lock lock(mutex);
    if (!ready) return false;

    write_filename = filename;
    if (write_filename.empty()) {
      write_error(gettext("No file to print specified"));
      return false;
    }

    mode = file_mode;

    ready = false;
  }

  ref();
  print_notifier();
  return true;
}
