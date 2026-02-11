attach_section_to_segment(const Target* target, Output_section* os)
{
  if ((os->flags() & elfcpp::SHF_ALLOC) == 0)
    this->unattached_section_list_.push_back(os);
  else
    this->attach_allocated_section_to_segment(target, os);
}
