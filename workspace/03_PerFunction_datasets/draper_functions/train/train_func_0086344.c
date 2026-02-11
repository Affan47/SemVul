core_io_memory_handler(char *t, const char *f, const char *m) {
  if (t == NULL) {
    std::cout << "\n memory_handler";
    std::cout << "::" << f << "::" << m;
    std::cout << "memory exhausted\n";
    std::cout.flush();
    abort();
  }
}
