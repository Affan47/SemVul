operator++()
  {
    if (this->off_ == this->afile_->filesize())
      return *this;
    this->off_ += sizeof(Archive_header);
    if (!this->afile_->is_thin_archive())
      this->off_ += this->header_.size;
    if ((this->off_ & 1) != 0)
      ++this->off_;
    this->read_next_header();
    return *this;
  }
