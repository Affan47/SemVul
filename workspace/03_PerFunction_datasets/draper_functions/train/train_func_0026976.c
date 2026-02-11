reopen_descriptor()
{
  if (!this->is_descriptor_opened_)
    {
      this->descriptor_ = open_descriptor(this->descriptor_,
					  this->name_.c_str(),
					  O_RDONLY);
      if (this->descriptor_ < 0)
	gold_fatal(_("could not reopen file %s"), this->name_.c_str());
      this->is_descriptor_opened_ = true;
    }
}
