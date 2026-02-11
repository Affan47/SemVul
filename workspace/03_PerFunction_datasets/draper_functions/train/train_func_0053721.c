got_entry_count() const
  {
    if (this->got_ == NULL)
      return 0;
    return this->got_size() / 4;
  }
