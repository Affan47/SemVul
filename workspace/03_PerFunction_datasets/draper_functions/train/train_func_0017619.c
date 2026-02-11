Unclaim(uint64_t start, uint64_t length) {
    if (length == 0) return;
    uint64_t end = start + length;
    lock_.lock();
    for (std::list<chunk_t>::iterator c = chunks_.begin();
         c != chunks_.end(); ++c) {
      if ((end >= c->start) && (end <= c->end)) {
        if (start < c->start) c->start = start;
        lock_.unlock();
        return;
      }
      if ((start <= c->end) && (start >= c->start)) {
        if (end > c->end) {
          c->end = end;
          std::list<chunk_t>::iterator c_ = c;
          ++c_;
          while (c_ != chunks_.end())
            if (c->end >= c_->start) {
              if (c_->end >= c->end) {
                c->end = c_->end;
                break;
              }
              c_ = chunks_.erase(c_);
            }
            else break;
        }
        lock_.unlock();
        return;
      }
      if ((start <= c->start) && (end >= c->end)) {
        c->start = start;
        if (end > c->end) {
          c->end = end;
          std::list<chunk_t>::iterator c_ = c;
          ++c_;
          while (c_ != chunks_.end())
            if (c->end >= c_->start) {
              if (c_->end >= c->end) {
                c->end = c_->end;
                break;
              }
              c_ = chunks_.erase(c_);
            }
            else break;
        }
        lock_.unlock();
        return;
      }
      if (end < c->start) {
        chunk_t chunk = {
          start, end
        };
        chunks_.insert(c, chunk);
        lock_.unlock();
        return;
      }
    }
    chunk_t chunk = {
      start, end
    };
    chunks_.push_back(chunk);
    lock_.unlock();
  }
