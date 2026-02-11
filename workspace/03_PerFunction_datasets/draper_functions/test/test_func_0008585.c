Clear()
  {
    DBG_START_METH("FilterLineSearch::Filter::Clear", dbg_verbosity);
    while (!filter_list_.empty()) {
      FilterEntry* entry = filter_list_.back();
      filter_list_.pop_back();
      delete entry;
    }
  }
