create_sections(Layout* layout)
{
  if (this->output_section_ != NULL)
    return;
  for (Output_section_elements::const_iterator p = this->elements_.begin();
       p != this->elements_.end();
       ++p)
    {
      if ((*p)->needs_output_section())
	{
	  const char* name = this->name_.c_str();
	  this->output_section_ =
	    layout->make_output_section_for_script(name, this->section_type());
	  return;
	}
    }
}
