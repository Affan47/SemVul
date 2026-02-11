FreeAll() {
  for (std::vector<void *>::const_iterator i(free_list_.begin()); i != free_list_.end(); ++i) {
    free(*i);
  }
  free_list_.clear();
  current_ = NULL;
  current_end_ = NULL;
}
