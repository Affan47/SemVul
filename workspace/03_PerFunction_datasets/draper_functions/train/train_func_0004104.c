list_updated(const KeyInfo * ki)
  {
    if (strcmp(ki->name, "filter-path") == 0) {
      filter_modes_.reset(0);
    }
    return no_err;
  }
