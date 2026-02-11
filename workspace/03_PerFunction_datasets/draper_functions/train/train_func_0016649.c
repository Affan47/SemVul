read_next_header()
{
  off_t filesize = this->afile_->filesize();
  while (true)
    {
      if (filesize - this->off_ < static_cast<off_t>(sizeof(Archive_header)))
	{
	  if (filesize != this->off_)
	    {
	      error_at(this->afile_->location(),
		       "%s: short archive header at %lu",
		       this->afile_->filename().c_str(),
		       static_cast<unsigned long>(this->off_));
	      this->off_ = filesize;
	    }
	  this->header_.off = filesize;
	  return;
	}

      char buf[sizeof(Archive_header)];
      if (!this->afile_->read(this->off_, sizeof(Archive_header), buf))
	{
	  this->header_.off = filesize;
	  return;
	}

      const Archive_header* hdr = reinterpret_cast<const Archive_header*>(buf);
      if (!this->afile_->interpret_header(hdr, this->off_, &this->header_.name,
					  &this->header_.size,
					  &this->header_.nested_off))
	{
	  this->header_.off = filesize;
	  return;
	}
      this->header_.off = this->off_;


      if (!this->header_.name.empty() && this->header_.name != "/")
	return;

      this->off_ += sizeof(Archive_header) + this->header_.size;
      if ((this->off_ & 1) != 0)
	++this->off_;
    }
}
