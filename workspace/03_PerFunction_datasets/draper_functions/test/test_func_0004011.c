TestNew(void* (*func)(size_t)) {
  news_handled = 0;


  std::new_handler saved_handler = std::set_new_handler(0);
  TestOneNew(func);


  std::set_new_handler(TestNewHandler);
  TestOneNew(func);
  if (news_handled != 1) {
    fprintf(LOGSTREAM, "new_handler was not called.\n");
    abort();
  }
  std::set_new_handler(saved_handler);
}
