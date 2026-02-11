clear()
  {
    while (head_ != 0) {
      DictInfoNode * to_del = head_;
      head_ = head_->next;
      delete to_del;
    }
  }
