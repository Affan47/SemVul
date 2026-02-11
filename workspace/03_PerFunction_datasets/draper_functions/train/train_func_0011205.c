data_segment_relro_end()
{
  if (this->saw_relro_end_)
    gold_error(_("DATA_SEGMENT_RELRO_END may only appear once "
		 "in a linker script"));
  this->saw_relro_end_ = true;

  if (!this->saw_data_segment_align_)
    gold_error(_("DATA_SEGMENT_RELRO_END must follow DATA_SEGMENT_ALIGN"));
  else
    {
      Sections_elements::iterator p = this->data_segment_align_start_;
      for (++p; p != this->sections_elements_->end(); ++p)
	(*p)->set_is_relro();
    }
}
